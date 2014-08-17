window.obMap = {
    "defaultParams": {
        "target": "mapdiv",
        "layers": [],
        "initExtent": {
            "x": -122.67419815,
            "y": 45.5284787580,
            "zoom": 11
        }
    },
    "maps": [],
    "layers": {},
    "layerList": {
        "layers": {},
        "layerOn": function(layerid) {
            var layer = {
                'id': layerid,
                'enabled': true
            };
            this.layers[layerid] = layer;
        },
        "layerOff": function(layerid) {
            if (_.isObject(this.layers[layerid])) {
                this.layers[layerid].enabled = false;
            }
        },
        "getActiveLayers": function( ) {
            return _.chain(this.layers).filter(function(l) {
                return l.enabled
            }).pluck('id').value();
        }
    },
    "activateLayer": function(layerid){
        var layerObj = this.layers[layerid];
        if(layerObj){
            var map = this.maps[0];
            if (map.hasLayer(layerObj.layer)) return;
            layerObj.layer.addTo(map);
            this.layerList.layerOn(layerid);
            layerObj.panHandler( );
        }
    },
    "activateLayers": function(layers){
        if(layers && layers.length){
            for(var i=0,l=layers.length;i<l;++i){
                this.activateLayer(layers[i]);
            }
        }
    },
    "deactivateLayer": function(layerid){
        var layerObj = this.layers[layerid];
        if(layerObj){
            var map = this.maps[0];
            if (!map.hasLayer(layerObj.layer)) return;
            map.removeLayer(layerObj.layer);
            this.layerList.layerOff(layerid);
        }
    },
    "deactivateAllLayers": function(){
        var activeLayers = this.layerList.getActiveLayers();
        for(var i=0,l=activeLayers.length;i<l;++i){
            this.deactivateLayer(activeLayers[i]);
        }
    },
    "selectors": {},
    // addMap ( )
    // Creates a map and does initial setup (layers, etc.)
    "addMap": function(params) {
        // Set defaults for any params not passed in
        var mapObj = {}, map, i, layer, layerObj, syncMove, baselayers, overlays = [], switcher, redrawOverlays, popup = L.popup( );

        params = $.extend(true, {}, this.defaultParams, params);

        // Create map object
        map = L.map(params.target);
        map.setView([params.initExtent.y, params.initExtent.x], params.initExtent.zoom);
        L.control.scale({position: "bottomright"}).addTo(map);

        // Default baselayer
        baselayers = {"Basemap": (L.tileLayer('http://tile.stamen.com/terrain/{z}/{x}/{y}.png').addTo(map))};

        switcher = L.control.layers(baselayers, {}, {'autoZIndex': true}).addTo(map);

        map.switcher = switcher;

        this.comment.control.addTo(map);

        // Add any layers passed in
        for (i = 0; i < params.layers.length; i++) {
            layer = params.layers[i];
            if (layer.type == 'geojson') {
                // Set up a GeoJSON layer
                layerObj = this.types.geojson(layer.params, map);
                map.on('moveend', layerObj.panHandler);
                map.on('zoomend', layerObj.panHandler);
            } else {
                // Otherwise, we assume it's a tile layer
                layerObj = this.types.tile(layer.params);
            }

            if (typeof (layer.id) != undefined) {
                layerObj.layer.layerId = layer.id;
            } else {
                layerObj.layer.layerId = _.uniqueId('obs_');
            }

            this.interface.addLayerSelectors(layerObj.layer.layerId, layer.params.selectors, layer.default);

            if (layer.default == true) {
                layerObj.layer.addTo(map);
                this.layerList.layerOn(layerObj.layer.layerId);
            }else{
                this.interface.disableLayerSelectors(layerObj);
            }

            layerObj.panHandler( );
            
            if(layer.addToLayerList){
                switcher.addOverlay(layerObj.layer, layer.title);
                map.on('overlayadd', layerObj.panHandler);
            }
            $('#update-button').on('click', layerObj.panHandler);
            overlays.push(layerObj);
            this.layers[layer.id] = layerObj;
        }

        map.on('overlayadd', obMap.interface.showLayerSelectors);
        map.on('overlayremove', obMap.interface.disableLayerSelectors);

        map.on('overlayadd', function(evt) {
            this.layerList.layerOn(evt.layer.layerId);
        }, obMap);
        map.on('overlayremove', function(evt) {
            this.layerList.layerOff(evt.layer.layerId);
        }, obMap);

        mapObj.map = map;
        this.maps.push(map);

        $('#update-button').on('click', function() {
            $('#update-button').addClass('btn-default').removeClass('btn-primary').addClass('disabled');
        });
        $('#selectors input,select').on('change', function() {
            $('#update-button').addClass('btn-primary').removeClass('btn-default').removeClass('disabled');
        });

        $('#update-button').on('click', function() {
            $('[id^=download]').removeClass('disabled');
        });
        $('#selectors input,select').on('change', function() {
            $('[id^=download]').addClass('disabled');
        });
    }
};

obMap.interface = {
    "addLayerSelectors": function(layerid, selectors, defaultState) {
        _.each(selectors, function(selector, key, list) {
            if (!_.has(obMap.selectors, selector)) {
                obMap.selectors[selector] = {
                    "container": $(selector),
                    "layers": {}
                };
            }
            obMap.selectors[selector]["layers"][layerid] = defaultState;
        });
    },
    "disableLayerSelectors": function(evt) {
        var layerId = evt.layer.layerId;
        _.each(obMap.selectors, function(selector, key, list) {
            if (_.has(selector.layers, layerId)) {
                selector.layers[layerId] = false;
                if (!_.contains(selector.layers, true)) {
                    $(selector.container).slideUp();
                }
            }
        });
    },
    "showLayerSelectors": function(evt) {
        var layerId = evt.layer.layerId;
        _.each(obMap.selectors, function(selector, key, list) {
            if (_.has(selector.layers, layerId)) {
                selector.layers[layerId] = true;
                $(selector.container).slideDown();
            }
        });
    }
};

obMap.comment = {
    "shim": L.rectangle([[-90, -180], [90, 180]], {'color': '#3c11c6', 'fillOpacity': 0.3}),
    "startComment": function(e) {
        var map = e.data;

        obMap.comment.shim.once('click', obMap.comment.showCommentForm, map);

        obMap.comment.control.removeFrom(map);

        obMap.comment.shim.addTo(map);
        obMap.comment.optionsControl.addTo(map);
    },
    "hideComment": function(e) {
        var map = e.data;

        map.removeLayer(obMap.comment.shim);

        obMap.comment.optionsControl.removeFrom(map);
        obMap.comment.control.addTo(map);

        $('#comment-modal input[type=text],textarea').val('');
        $('input.required,textarea.required').parents('.has-feedback').removeClass('has-error').removeClass('has-success');
        $('input.required,textarea.required').siblings('.form-control-feedback').removeClass('glyphicon-ok').removeClass('glyphicon-remove');
        $('#comment-modal #comment-text').html('');
    },
    "saveComment": function(e) {
        var data = {
            'name': $('#comment-form input[name=commenter-name]').val(),
            'title': $('#comment-form input[name=comment-title]').val(),
            'lonlat': $('#comment-form input[name=comment-lonlat]').val(),
            'text': $('#comment-form textarea[name=comment-text]').val(),
            'layer': $('#comment-form input[type=radio]:checked').val()
        };

        $.ajax({
            'url': BASE_DIR + '../api/submit/comment',
            'type': 'POST',
            'data': data,
            'timeout': 10000,
            'success': function(data) {
                console.log(data);
            }
        });

        $('#comment-modal').modal('hide');
    },
    "showCommentForm": function(e) {
        if (typeof e.latlng != 'undefined') {
            var point = e.latlng;
            var map = this;

            $('[name=comment-lonlat]').val(Math.round(point.lng * 1000000) / 1000000 + ', ' + Math.round(point.lat * 1000000) / 1000000);
        } else {
            var map = e.data;
            $('[name=comment-lonlat]').val('');
        }

        $('#comment-save').one('click', map, obMap.comment.saveComment);

        $('#comment-modal').modal('show')
                .one('hidden.bs.modal', map, obMap.comment.hideComment);
    }
};

obMap.comment.optionsControl = L.control({'position': 'bottomleft'});

obMap.comment.optionsControl.onAdd = function(map) {
    var div = $('<div/>');
    var cancel = $('<button/>');

    $(cancel).addClass('btn btn-xs btn-danger')
            .attr('data-toggle', 'tooltip')
            .attr('title', 'Cancel')
            .tooltip({'delay': {'show': 500, 'hide': 250}})
            .html('<span class="glyphicon glyphicon-remove"></span>')
            .one('click', map, obMap.comment.hideComment);

    var button = $('<button/>');
    $(button).addClass('btn btn-xs btn-info')
            .attr('data-toggle', 'tooltip')
            .attr('title', 'Make a pointless comment')
            .tooltip({'delay': {'show': 500, 'hide': 250}})
            .html('<span class="glyphicon glyphicon-pencil"></span>')
            .one('click', map, obMap.comment.showCommentForm);

    div.html('<b>Click on the map to specify a comment point.</b>').append(button).append(cancel);
    div.addClass('comment-instructions-control');

    return div[0];
};

obMap.comment.control = L.control({'position': 'bottomleft'});

obMap.comment.control.onAdd = function(map) {
    var button = $('<button/>');
    $(button).addClass('btn btn-sm btn-default')
            .attr('data-toggle', 'tooltip')
            .attr('title', 'Make a comment')
            .tooltip({'placement': 'right', 'delay': {'show': 500, 'hide': 100}})
            .html('<span class="glyphicon glyphicon-flag"></span>')
            .one('click', map, obMap.comment.startComment);

    return button[0];
};

obMap.types = {
    "getBounds": function(layer, bounded, map) {
        var data = [];
        if (bounded == true) {
            data.push(map.getBounds( ).toBBoxString( ));
            data.push(map.getZoom( ));
        }
        return data;
    },
    "getQueryData": function( ) {
        var data = {};
        $("#selectors input,select").each(
                function(index, selector) {
                    data[selector.name] = $(selector).val( );
                }
        );
        return data;
    },
    "getRedrawLayer": function(layer) {
        var redraw = function(data) {
            layer.clearLayers( );
            layer.addData(data);
            layer.bringToBack();
        };
        return redraw;
    },
    "geojson": function(params, map) {
        var layerObj = {};
        var defaultParams = {
            "styleDefs": null,
            "baseStyle": null,
            "popupFunc": null,
            "source": {
                "url": null,
                "bounded": true,
                "data": {}
            },
            "style": function(feature) {
            }
        };
        params = $.extend(true, defaultParams, params);
        var styleFunc,pointToLayer;
        styleFunc = function( ) {
            return null;
        };

        if (typeof params.styles != 'undefined') {
            styleFunc = function(feature) {
                return params.styles[feature.properties[params.styleAttrib]];
            };
            pointToLayer = function(feature, coords) {
                var style = _.defaults(params.styles[feature.properties[params.styleAttrib]], params.baseStyle);
                return L.circleMarker(coords, style);
            };
        }

        if (params.styleDefs != null) {
            pointToLayer = function(feature, coords) {
                var baseStyle = params.baseStyle;
                var style;
                var styleDefs = params.measureSelector? params.styleDefs[$("[name=" + params.measureSelector + "]").val()] : params.styleDefs;
                var measure = params.measureFunc? params.measureFunc(feature) : feature.properties[$("[name=" + params.measureSelector + "]").val()];
                for (i = 0; i < styleDefs.length; i++) {
                    var styleDef = styleDefs[i];
                    if ((styleDef.mode == 'LT') && (measure < styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'BET') && (measure >= styleDef.min) && (measure < styleDef.max)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'GT') && (measure >= styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'EQ') && (measure == styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    }
                }
                return L.circleMarker(coords, style);
            };
            styleFunc = function(feature) {
                var baseStyle = params.baseStyle;
                var style;
                var styleDefs = params.measureSelector? params.styleDefs[$("[name=" + params.measureSelector + "]").val()] : params.styleDefs;
                var measure = params.measureFunc? params.measureFunc(feature) : feature.properties[$("[name=" + params.measureSelector + "]").val()];
                for (i = 0; i < styleDefs.length; i++) {
                    var styleDef = styleDefs[i];
                    if ((styleDef.mode == 'LT') && (measure < styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'BET') && (measure >= styleDef.min) && (measure < styleDef.max)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'GT') && (measure >= styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    } else if ((styleDef.mode == 'EQ') && (measure == styleDef.val)) {
                        style = $.extend(true, {}, baseStyle, styleDef.style);
                        break;
                    }
                }
                return style;
            };
        }

        var layer = L.geoJson(null,
                {
                    "style": styleFunc,
                    "pointToLayer": pointToLayer,
                    "onEachFeature": params.popupFunc
                }
        );

        if (params.source.url != null) {
            var source = params.source;

            var layerCallback = this.getRedrawLayer(layer);

            var panHandler = function(e) {
                if (!map.hasLayer(layer)) {
                    return;
                }
                if (e != undefined && e.type == "overlayadd" && layer != e.layer) {
                    return;
                }
                var bounds = obMap.types.getBounds(layer, source.bounded, map);
                var url = source.url + bounds.join('/');
                var data = obMap.types.getQueryData( );
                $.getJSON(url, data, layerCallback);
            };

            layerObj.panHandler = panHandler;
        }
        layerObj.layer = layer;
        return layerObj;
    }
};