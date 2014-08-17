var requiredFeedback = function(e) {
    var val = $(e.target).val();
    if (val.length == 0) {
        $(e.target).removeClass('has-success').addClass('has-error');
        $(e.target).parents('.has-feedback').removeClass('has-success').addClass('has-error');
        $(e.target).siblings('.form-control-feedback').addClass('glyphicon-remove').removeClass('glyphicon-ok');
    } else {
        $(e.target).removeClass('has-error').addClass('has-success');
        $(e.target).parents('.has-feedback').removeClass('has-error').addClass('has-success');
        $(e.target).siblings('.form-control-feedback').addClass('glyphicon-ok').removeClass('glyphicon-remove');
    }
};

$('.required').blur(requiredFeedback);

var guide = {
    'list': null,
    'data': null,
    'measureData': null,
    'measureField': 'avg-volume-per-lane',
    'layerInUse': null,
    'guideInfo': null,
    'init': function() {
        $('#guide-selection-group select[name=guide_selection]').on( "change", function( event ) {
            guide.select($(this).val());
          });

        
        $('#guide-form select[name=guide-type]').on( "change", function( event ) {
            guide.updateSelectors();
          });        
          
        $("#guide_hour_slider").slider({
            value: 0,
            min: 0,
            max: 23.75,
            step: 0.25,
            slide: function(event, ui) {
                var val = ui.value, h = Math.floor(val), m = Math.floor((val % 1) * 60);
                $("#guide_hour_text").html((h < 10? "0" : "")+h + ":" + (m < 10? "0" : "")+m);
            },
            stop: function( event, ui ) {
                guide.filterData();
            }
        });
        
        //$('#guide-modal').on('show.bs.modal', guide.new);
        
        $('#volume-report-modal').on('show.bs.modal', function(){
            $('#volume-report-form')[0].reset();
            $('#volume-report-form > .has-feedback').removeClass('has-success').removeClass('has-error');
            $('#volume-report-form .form-control-feedback').removeClass('glyphicon-ok').removeClass('glyphicon-remove');
            
            $('#volume-report-download-button').one('click', function(){
                $('#volume-report-form')[0].submit();
            });
            
        });
        
        $('#speed-report-modal').on('show.bs.modal', function(){
            $('#speed-report-form')[0].reset();
            $('#speed-report-form > .has-feedback').removeClass('has-success').removeClass('has-error');
            $('#speed-report-form .form-control-feedback').removeClass('glyphicon-ok').removeClass('glyphicon-remove');
            
            $('#speed-report-download-button').one('click', function(){
                $('#speed-report-form')[0].submit();
            });
            
        });
        
        this.reloadList();
    },
    'updateSelectors': function(){
        var val = $('#guide-form select[name=guide-type]').val();
        if(val == "weather-temp"){
            $("#guide-year-group").slideUp();
            $("#guide-date-group").slideDown();
        }else{
            $("#guide-year-group").slideDown();
            $("#guide-date-group").slideUp();
        }
    },
    'new': function( ) {
        $('#guide-modal').modal({show:true});
        var start_time, end_time, layers;

        $('#guide-form')[0].reset();
        $('#guide-form > .has-feedback').removeClass('has-success').removeClass('has-error');
        $('#guide-form .form-control-feedback').removeClass('glyphicon-ok').removeClass('glyphicon-remove');

        start_time = $('[name=start-time]').val();
        end_time = $('[name=end-time]').val();

        layers = obMap.layerList.getActiveLayers();

        _.each(obMap.layerList.getActiveLayers(), function(layer) {
            $('#guide-form input[name=' + layer + ']').prop('checked', true);
        });
        
        $('.input-group.date .input-sm').datepicker('update', Date());

        $('[name=guide-start-time]').val(start_time);
        $('[name=guide-end-time]').val(end_time);

        $('#guide-save').prop('disabled', true);
        this.updateSelectors();
        
    },
    'edit': function( ) {
        var guide_id = +$('#guide-selection-group select[name=guide_selection]').val();
        if(!guide_id) return;
        
        $('#guide-modal').modal({show:true});
        var guide_info = _.find(this.list,function(guide){ return guide.id == guide_id; });

        $('#guide-form')[0].reset();
        $('#guide-form > .has-feedback').removeClass('has-success').removeClass('has-error');
        $('#guide-form .form-control-feedback').removeClass('glyphicon-ok').removeClass('glyphicon-remove');

        $('#guide-form select[name=guide-type]').val(guide_info.type);
        $('#guide-form input[name=guide-name]').val(guide_info.name);
        $('#guide-form textarea[name=guide-description]').val(guide_info.desc);
        
        var params = guide_info.params;
        
        params.year && $('#guide-form input[name=guide-year]').val(params.year);
        params.date && $('#guide-form input[name=guide-date]').val(params.date);
        
        $('#guide-form input[name=guide-region][value="'+(params.region || params.city)+'"]').prop('checked',true);
        $('#guide-form input[name=guide-start-time]').val(params.restrict_time_from);
        $('#guide-form input[name=guide-end-time]').val(params.restrict_time_to);

        _.each(guide_info.layers, function(layer) {
            $('#guide-form input[name=' + layer + ']').prop('checked', true);
        });

        $('#guide-save').prop('disabled', false);
        this.updateSelectors();
    },
    'doAdd': function(  ) {
        var data = {
            'guide_type': $('#guide-form select[name=guide-type]').val(),
            'name': $('#guide-form input[name=guide-name]').val(),
            'desc': $('#guide-form textarea[name=guide-description]').val(),
            'layers': _.map($('#guide-form input[type=checkbox]:checked'), function(check) {
                return $(check).val()
            }),
            'year': $('#guide-form input[name=guide-year]').val(),
            'date': $('#guide-form input[name=guide-date]').val(),
            'start_time': $('#guide-form input[name=guide-start-time]').val(),
            'end_time': $('#guide-form input[name=guide-end-time]').val(),
            'region': $('#guide-form input[name=guide-region]:checked').val()
        };

        $.ajax({
            'url': BASE_DIR + '../api/guide/add',
            'type': 'POST',
            'data': data,
            'timeout': 10000,
            'success': function(data) {
                guide.reloadList();
                console.log(data);
            }
        });

        $('#guide-modal').modal('hide');
    },
    'doEdit': function(  ) {
        var data = {
            'guide_id': $('#guide-selection-group select[name=guide_selection]').val(),
            'guide_type': $('#guide-form select[name=guide-type]').val(),
            'name': $('#guide-form input[name=guide-name]').val(),
            'desc': $('#guide-form textarea[name=guide-description]').val(),
            'layers': _.map($('#guide-form input[type=checkbox]:checked'), function(check) {
                return $(check).val()
            }),
            'year': $('#guide-form input[name=guide-year]').val(),
            'date': $('#guide-form input[name=guide-date]').val(),
            'start_time': $('#guide-form input[name=guide-start-time]').val(),
            'end_time': $('#guide-form input[name=guide-end-time]').val(),
            'region': $('#guide-form input[name=guide-region]:checked').val()
        };

        $.ajax({
            'url': BASE_DIR + '../api/guide/edit',
            'type': 'POST',
            'data': data,
            'timeout': 10000,
            'success': function(data) {
                guide.reloadList();
                console.log(data);
            }
        });

        $('#guide-modal').modal('hide');
    },
    'reloadList': function() {
        $.ajax({
            'url': BASE_DIR + '../api/guide/guide_list',
            'type': 'POST',
            'timeout': 10000,
            'success': function(data) {
                eval("data = " + data + ";");
                
                var html = _.reduce(data, function(sel_options, guide) {
                    return sel_options += '<option value="' + guide.id + '">' + guide.name + '</option>';
                }, '<option value="0">Select a Guide</option>');
                $('#guide-selection-group select[name=guide_selection]').html(html);
                
                // Extract the data from the layers and params attributes.
                _.each(data, function(guide){
                    guide.layers = guide.layers? guide.layers.split("|") : [];
                    
                    if(guide.params){
                        var params = guide.params.split("|");
                        guide.params = _.reduce(params,function(po, param){
                            // The param comes in the form of "(<name>,<value>)". So, we need to extract the name and value.
                            var pair = param.substring(1,param.length-1).split(",");
                            po[pair[0]] = pair[1];
                            return po;
                        },{});
                    }else{
                        guide.params = {};
                    }
                    
                    // Determine the guide type.
                    switch(guide.guide_id){
                        case "traffic":
                            switch(guide.params.report_type){
                                case "speed":
                                    guide.type = 'traffic-speed';
                                    break;
                                case "volume":
                                    guide.type = 'traffic-volume';
                                    break;
                                default:
                                    guide.type = null;
                                    break;
                            }
                            break;
                        case "temperature_area":
                            guide.type = 'weather-temp';
                            break;
                        default:
                            guide.type = null;
                            break;
                    }
                    
                    
                });
                guide.list = data;
            }
        });
    },
    'select': function(id) {
        this.guideInfo = _.find(this.list,function(guide){ return guide.id == id; });
        if(this.guideInfo){
            // Activate the appropriate layer for this guide.
            obMap.deactivateAllLayers();
            this.layerInUse = this.guideInfo.type;
            switch(this.guideInfo.type){
                case 'weather-temp':
                    $( "#guide_hour_slider" ).slider( "option", "step", 1 ).slider( "option", "max", 23 );
                    break;
                default:
                    $( "#guide_hour_slider" ).slider( "option", "step", 0.25 ).slider( "option", "max", 23.75 );
            }
            this.layerInUse && obMap.activateLayer(this.layerInUse); 
            obMap.activateLayers(this.guideInfo.layers); 
            
            $.ajax({
                'url': BASE_DIR + '../api/guide/query?guide_id=' + id,
                'type': 'POST',
                'timeout': 180000,
                'success': function(data) {
                    eval("guide.data = " + data + ";");
                    guide.filterData();
                }
            });
        }else{
            
        }
    },
    'filterData': function(){
        if(!this.data) return;
        var hour = $("#guide_hour_slider").slider( "value" );
        switch(this.guideInfo.type){
            case 'traffic-volume':
            case 'traffic-speed':
                var filteredData = _.filter(this.data,function(row){ return row['time'] == hour; })
                this.measureData = {};
                for(var i=0,l=filteredData.length,r;i<l;++i){
                    r = filteredData[i];
                    this.measureData[r.stationid] = r;
                };
                this.layerInUse && obMap.layers[this.layerInUse].panHandler();
                break;
                
            case 'weather-temp':
                this.measureData = {};
                this.measureData[this.guideInfo.params.city] = _.filter(this.data,function(row){ 
                    var t = row['time'];
                    if(!t) return false;
                    var m = t.match(/\d+-\d+-\d+\s+(\d+):\d+:\d+/);
                    return +m[1] == hour; 
                })[0];
                this.layerInUse && obMap.layers[this.layerInUse].panHandler();
                break;
        }
    }
};

$(function( ) {
    guide.init();
}
);
