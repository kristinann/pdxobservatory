// Define the base directory for this JavaScript file.
var scripts = document.getElementsByTagName("script");
var BASE_DIR = scripts[scripts.length - 1].src;
BASE_DIR = BASE_DIR.substring(0, BASE_DIR.lastIndexOf("/") + 1);

var map1 = {
    "target": "mapdiv1",
    "layers": [
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Bicycle Routes",
            "id": "layer-bicycle-routes",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/bike_rte/"
                },
                "styleAttrib": "bikemode",
                "styles": {
                    "Regional multi-use path": {
                        "color": "#c500ff",
                        "weight": 4,
                        "opacity": 0.8
                    },
                    "Local multi-use path": {
                        "color": "#c500ff",
                        "weight": 3,
                        "opacity": 0.8
                    },
                    "Bike boulevard": {
                        "color": "#0070ff",
                        "weight": 4,
                        "opacity": 0.8
                    },
                    "Bike lane": {
                        "color": "#0070ff",
                        "weight": 3,
                        "opacity": 0.8
                    },
                    "Low traffic through street": {
                        "color": "#38a800",
                        "weight": 3,
                        "opacity": 0.8
                    },
                    "Moderate traffic through street": {
                        "color": "#aa0",
                        "weight": 4,
                        "dash-array": "5,1",
                        "opacity": 0.8
                    },
                    "High traffic through street": {
                        "color": "#fa0",
                        "weight": 3,
                        "opacity": 0.8
                    },
                    "Caution area": {
                        "color": "#f40",
                        "weight": 4,
                        "dash-array": "5,1",
                        "opacity": 0.8
                    },
                    "Planned bike lane": {
                        "color": "#bed2ff",
                        "weight": 4,
                        "dash-array": "3,2",
                        "opacity": 0.8
                    },
                    "Planned multi-use path": {
                        "color": "#e8beff",
                        "weight": 4,
                        "dash-array": "3,2",
                        "opacity": 0.8
                    }
                },
                "popupFunc": function(feature, layer) {
                    popup = '<b>Path type:</b> ' + feature.properties.bikemode + '<br>';
                    popup += '<b>Location:</b> ' + feature.properties.streetname + ' ' + feature.properties.ftype;
//          layer.on ( 'click', function ( e ) { console.log ( 'featclick', foo = e ); } );
                    layer.bindPopup(popup);
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Counties",
            "id": "layer-counties",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/co_fill_2013_05/"
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Parking Meters",
            "id": "layer-parking",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/meters/"
                },
                "styleAttrib": "duration",
                "styles": {
                    "0": {"fillColor": "#fcfbfd"},
                    "11": {"fillColor": "#efedf5"},
                    "15": {"fillColor": "#dabaeb"},
                    "60": {"fillColor": "#bcbddc"},
                    "90": {"fillColor": "#9e9ac8"},
                    "120": {"fillColor": "#807dba"},
                    "180": {"fillColor": "#6a51a3"},
                    "300": {"fillColor": "#4a1486"}
                },
                "popupFunc": function(feature, layer) {
                    var duration = (feature.properties.duration >= 60) ? feature.properties.duration / 60 + ' hour' + ((feature.properties.duration / 60 > 1) ? 's' : '') : feature.properties.duration + ' minutes';
                    popup = '<b>Meter ID:</b> ' + feature.properties.assetid + '<br>';
                    popup += '<b>Duration:</b> ' + duration + '<br>';
                    popup += '<b>Number of spaces:</b> ' + feature.properties.numspaces + '<br>';
                    popup += '<b>Owner:</b> ' + feature.properties.owner;
                    layer.bindPopup(popup);
                    layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                    });
                },
                "baseStyle": {
                    "radius": 8,
                    "fillColor": "#5f5",
                    "color": "#000",
                    "weight": 1,
                    "opacity": 1,
                    "fillOpacity": 1
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "School Sites",
            "id": "layer-school-sites",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/school_site_2013_05/"
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Vegetation",
            "id": "layer-vegetation",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/vegetation_pdx/"
                },
                "style": {
                    "color": "#afa",
                    "stroke": false,
                    "fillOpacity": 1
                }
            }
        },
        /*
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Taxlots",
            "id": "layer-taxlots",
            "params": {
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/taxlots_2013_05/"
                }
            }
        },
        */
        {
            "type": "geojson",
            "default": true,
            "addToLayerList": true,
            "title": "Air Quality",
            "id": "layer-deq",
            "params": {
                "styleDefs": {
                    "sd_hor_wind_dir": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 19.9800004, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 19.9800004, "max": 39.9600008, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 39.9600008, "max": 59.9400012, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 59.9400012, "max": 79.9200016, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 79.9200016, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "upper_level_temp": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": -19.0399992, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": -19.0399992, "max": -6.2799994, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": -6.2799994, "max": 6.48000039999999, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 6.48000039999999, "max": 19.2400002, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 19.2400002, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "nitric_oxide": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 217.057176, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 217.057176, "max": 988.713532, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 988.713532, "max": 1760.369888, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 1760.369888, "max": 2532.026244, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 2532.026244, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "wind_speed": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 28.9652, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 28.9652, "max": 57.9304, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 57.9304, "max": 86.8956, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 86.8956, "max": 115.8608, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 115.8608, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "barometric_pressure": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 23.684848, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 23.684848, "max": 25.369696, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 25.369696, "max": 27.054544, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 27.054544, "max": 28.739392, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 28.739392, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "resultant_direction": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 93, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 93, "max": 186, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 186, "max": 279, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 279, "max": 372, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 372, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "nitrogen_dioxide": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 1912.39236424, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 1912.39236424, "max": 3830.52767318, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 3830.52767318, "max": 5748.66298212, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 5748.66298212, "max": 7666.79829106, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 7666.79829106, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "sulfur_dioxide": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 1.00028464, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 1.00028464, "max": 6.99966948, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 6.99966948, "max": 12.99905432, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 12.99905432, "max": 18.99843916, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 18.99843916, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "solar_radiation": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 0.3074, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 0.3074, "max": 0.6298, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 0.6298, "max": 0.9522, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 0.9522, "max": 1.2746, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 1.2746, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "relative_humidity": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 25.630854, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 25.630854, "max": 44.261708, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 44.261708, "max": 62.892562, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 62.892562, "max": 81.523416, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 81.523416, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "nitrogen_oxides": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 2176.81924, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 2176.81924, "max": 4353.63518, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 4353.63518, "max": 6530.45112, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 6530.45112, "max": 8707.26706, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 8707.26706, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "middle_level_temperature": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": -22.299998, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": -22.299998, "max": -4.499998, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": -4.499998, "max": 13.300002, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 13.300002, "max": 31.100002, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 31.100002, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "resultant_speed": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 28.965206, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 28.965206, "max": 57.930412, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 57.930412, "max": 86.895618, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 86.895618, "max": 115.860824, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 115.860824, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "delta_temperature": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": -1.36800004, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": -1.36800004, "max": 0.28399992, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 0.28399992, "max": 1.93599988, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 1.93599988, "max": 3.58799984, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 3.58799984, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "carbon_monoxide": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 1883796.584, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 1883796.584, "max": 3792992.188, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 3792992.188, "max": 5702187.792, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 5702187.792, "max": 7611383.396, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 7611383.396, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "ozone": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 5.16071359992, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 5.16071359992, "max": 10.32553519994, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 10.32553519994, "max": 15.49035679996, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 15.49035679996, "max": 20.65517839998, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 20.65517839998, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "lower_level_temperature": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": -25.200001, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": -25.200001, "max": -10.200001, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": -10.200001, "max": 4.799999, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 4.799999, "max": 19.799999, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 19.799999, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "temperature": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": -10.895979, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": -10.895979, "max": 4.308042, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 4.308042, "max": 19.512063, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 19.512063, "max": 34.716084, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 34.716084, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "light_scatter": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 13.50835168, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 13.50835168, "max": 29.87670326, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 29.87670326, "max": 46.24505484, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 46.24505484, "max": 62.61340642, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 62.61340642, "style": {"fillColor": "#ffffb2"}}
                    ]
                },
                "baseStyle": {
                    "radius": 10,
                    "fillColor": "#5f5",
                    "color": "#000",
                    "weight": 1,
                    "opacity": 1,
                    "fillOpacity": 1
                },
                "selectors": [
                    "#time-range-group",
                    "#date-range-group",
                    "#deq-measure-group",
                    "#download-deq-group",
                    "#update-group"
                ],
                "measureSelector": "deq-measure",
                "popupFunc": function(feature, layer) {
                    layer.bindPopup($("option[value=" + $("[name=deq-measure]").val( ) + "]").html() + ' : ' + feature.properties[$("[name=deq-measure]").val( )]);
//          layer.on ( 'click', function ( e ) { console.log ( feature, 'featclick', foo = e ); } );
                },
                "source": {
                    "url": BASE_DIR + "../api/deq/deq_stations/"
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": true,
            "title": "Transit",
            "id": "layer-busstops",
            "params": {
                "baseStyle": {
                    "radius": 8,
                    "fillColor": "#888",
                    "color": "#555",
                    "weight": 1,
                    "opacity": 1,
                    "fillOpacity": 1
                },
                "styleDefs": {
                    "on_time": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 60.0, "style": {"fillColor": "#d7191c"}},
                        {"mode": "BET", "min": 60.0, "max": 70.0, "style": {"fillColor": "#fdae61"}},
                        {"mode": "BET", "min": 70.0, "max": 80.0, "style": {"fillColor": "#ffffbf"}},
                        {"mode": "BET", "min": 80.0, "max": 90.0, "style": {"fillColor": "#abd9e9"}},
                        {"mode": "BET", "min": 90.0, "max": 100.0, "style": {"fillColor": "#2c7bb6"}}
                    ],
                    "ons": [
                        {"mode": "DYN", "url": BASE_DIR + "../api/transit/breaks/ons/"}
                    ]
                },
                "selectors": [
                    "#time-range-group",
                    "#date-range-group",
                    "#transit-measure-group",
                    "#timeofday-group",
                    "#service-key-group",
                    "#update-group"
                ],
                "measureSelector": "transit-measure",
                "popupFunc": function(feature, layer) {
                    popup = '<b>Percent early:</b> ' + feature.properties.early + '<br>';
                    popup += '<b>Percent on time:</b> ' + feature.properties.on_time + '<br>';
                    popup += '<b>Percent late:</b> ' + feature.properties.late + '<br>';

                    layer.bindPopup(popup);
                    layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                    });
                },
                "source": {
                    "url": BASE_DIR + "../api/transit/stops/"
                }
            }
        },
        {
            "type": "geojson",
            "default": true,
            "addToLayerList": true,
            "title": "Travel Time",
            "id": "layer-bluetooth",
            "params": {
                "baseStyle": {
                    "opacity": 0.8,
                    "weight": 10
                },
                "styleDefs": {
                    "pct_avg_tt": [
                        {"mode": "EQ", "val": null, "style": {"color": "#bbb"}},
                        {"mode": "LT", "val": 60, "style": {"color": "#4575b4"}},
                        {"mode": "BET", "min": 60, "max": 80, "style": {"color": "#91bfdb"}},
                        {"mode": "BET", "min": 80, "max": 100, "style": {"color": "#e0f3f8"}},
                        {"mode": "BET", "min": 100, "max": 120, "style": {"color": "#ffffbf"}},
                        {"mode": "BET", "min": 120, "max": 140, "style": {"color": "#fee090"}},
                        {"mode": "BET", "min": 140, "max": 160, "style": {"color": "#fc8d59"}},
                        {"mode": "GT", "val": 160, "style": {"color": "#d73027"}}
                    ]
                },
                "selectors": [
                    "#time-range-group",
                    "#date-range-group",
                    "#bt-measure-group",
                    "#update-group"
                ],
                "measureSelector": "bt-measure",
                "popupFunc": function(feature, layer) {
                    popup = '<b>Percent of expected traveltime:</b> ' + feature.properties.pct_avg_tt + '<br>';
                    popup += '<b>Expected traveltime:</b> ' + feature.properties.expected_traveltime + '<br>';
                    popup += '<b>Average actual traveltime:</b> ' + feature.properties.traveltime;
                    layer.bindPopup(popup);
                    layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                    });
                },
                "source": {
                    "url": BASE_DIR + "../api/bt/bt_segments/"
                }
            }
        },
        {
            "type": "geojson",
            "default": true,
            "addToLayerList": true,
            "title": "Weather",
            "id": "layer-weather",
            "params": {
                "styleDefs": {
                    "temp_c": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 0.98, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 0.98, "max": 9.76, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 9.76, "max": 18.54, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 18.54, "max": 27.32, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 27.32, "style": {"fillColor": "#ffffb2"}}
                    ],
                    "precip_1hr_metric": [
                        {"mode": "EQ", "val": null, "style": {"fillColor": "#bbb"}},
                        {"mode": "LT", "val": 1299.2, "style": {"fillColor": "#ffffb2"}},
                        {"mode": "BET", "min": 1299.2, "max": 5135.9, "style": {"fillColor": "#fecc5c"}},
                        {"mode": "BET", "min": 5135.9, "max": 8972.6, "style": {"fillColor": "#fd8d3c"}},
                        {"mode": "BET", "min": 8972.6, "max": 12809.3, "style": {"fillColor": "#f03b20"}},
                        {"mode": "GT", "val": 12809.3, "style": {"fillColor": "#ffffb2"}}
                    ],
                },
                "baseStyle": {
                    "radius": 10,
                    "fillColor": "#5f5",
                    "color": "#000",
                    "weight": 1,
                    "opacity": 1,
                    "fillOpacity": 1
                },
                "popupFunc": function(feature, layer) {
                    layer.bindPopup($("option[value=" + $("[name=weather-measure]").val( ) + "]").html() + ' : ' + feature.properties[$("[name=weather-measure]").val( )]);
                    layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                    });
                },
                "selectors": [
                    "#time-range-group",
                    "#date-range-group",
                    "#weather-measure-group",
                    "#download-weather-group",
                    "#update-group"
                ],
                "measureSelector": "weather-measure",
                "source": {
                    "url": BASE_DIR + "../api/weather/weather_stations/"
                },
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": false,
            "title": "Traffic: Volume",
            "id": "traffic-volume",
            "params": {
                "baseStyle": {
                    "opacity": 0.8,
                    "weight": 7
                },
                "styleDefs": [
                        {"mode": "EQ", "val": null, "style": {"color": null}},
                        {"mode": "EQ", "val": -1, "style": {"color": "#bbb"}},
                        {"mode": "LT", "val": 300, "style": {"color": "#05C116"}},
                        {"mode": "BET", "min": 300, "max": 500, "style": {"color": "#A6C105"}},
                        {"mode": "BET", "min": 500, "max": 1000, "style": {"color": "#FFDA00"}},
                        {"mode": "BET", "min": 1000, "max": 1300, "style": {"color": "#FF7300"}},
                        {"mode": "GT", "val": 1300, "style": {"color": "#FF1800"}}
                ],
                "measureFunc": function(feature) {
                    if(!guide.measureData) return null;
                    var row = guide.measureData[feature.properties.stationid];
                    return row? row.avgvolumepl * 4 : -1;
                },
                "popupFunc": function(feature, layer) {
                    if(!guide.measureData) return;
                    var row = guide.measureData[feature.properties.stationid];
                     var popup = '<b>Average volume per lane:</b> ' + (row? row.avgvolumepl * 4 : " data unavailable") + '<br>';
                     layer.bindPopup(popup);
                     /*
                     layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                     });*/
                },
                /*
                "selectors": [
                    "#guide-selection-group",
                    "#guide-slidebar-group",
                    "#guide-edit-group",
                    "#make-guide-group"
                ],*/
                "source": {
                    "url": BASE_DIR + "../api/map/highways/",
                    "include_scale": true
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "title": "Traffic: Speed",
            "id": "traffic-speed",
            "params": {
                "baseStyle": {
                    "opacity": 0.8,
                    "weight": 7
                },
                "styleDefs": [
                        {"mode": "EQ", "val": null, "style": {"color": null}},
                        {"mode": "EQ", "val": -1, "style": {"color": "#bbb"}},
                        {"mode": "LT", "val": 19, "style": {"color": "#FF1800"}},
                        {"mode": "BET", "min": 19, "max": 38, "style": {"color": "#FF7300"}},
                        {"mode": "BET", "min": 38, "max": 50, "style": {"color": "#FFDA00"}},
                        {"mode": "BET", "min": 50, "max": 75, "style": {"color": "#A6C105"}},
                        {"mode": "GT", "val": 75, "style": {"color": "#05C116"}}
                ],
                "measureFunc": function(feature) {
                    if(!guide.measureData) return null;
                    var row = guide.measureData[feature.properties.stationid];
                    return row? row.speed : -1;
                },
                "popupFunc": function(feature, layer) {
                    if(!guide.measureData) return;
                    var row = guide.measureData[feature.properties.stationid];
                     var popup = '<b>Average speed:</b> ' + (row? row.speed : " data unavailable") + '<br>';
                     layer.bindPopup(popup);
                     /*
                     layer.on('click', function(e) {
                        console.log('featclick', foo = e);
                     });*/
                },
                /*
                "selectors": [
                    "#guide-selection-group",
                    "#guide-slidebar-group",
                    "#guide-edit-group",
                    "#make-guide-group"
                ],*/
                "source": {
                    "url": BASE_DIR + "../api/map/highways/",
                    "include_scale": true
                }
            }
        },
        {
            "type": "geojson",
            "default": false,
            "addToLayerList": false,
            "title": "Weather: Temperature",
            "id": "weather-temp",
            "params": {
                "styleDefs": [
                    {"mode": "EQ", "val": null, "style": {"fillColor": "transparent"}},
                    {"mode": "LT", "val": 0.98, "style": {"fillColor": "#37a1f7"}},
                    {"mode": "BET", "min": 0.98, "max": 9.76, "style": {"fillColor": "#2bc4d8"}},
                    {"mode": "BET", "min": 9.76, "max": 18.54, "style": {"fillColor": "#ffffb2"}},
                    {"mode": "BET", "min": 18.54, "max": 27.32, "style": {"fillColor": "#ed8a3a"}},
                    {"mode": "GT", "val": 27.32, "style": {"fillColor": "#f03b20"}}
                ],
                "baseStyle": {
                    "radius": 10,
                    "weight": 1,
                    "opacity": 0.8,
                    "fillOpacity": 0.8
                },
                "measureFunc": function(feature) {
                    if(!guide.measureData) return null;
                    var row = guide.measureData[feature.properties.cityname.toLowerCase()];
                    return row? row.temperature : null;
                },
                "popupFunc": function(feature, layer) {
                    if(!guide.measureData) return;
                    var row = guide.measureData[feature.properties.cityname.toLowerCase()];
                    if(!row) return;
                     var popup = '<b>Temperature :</b> ' + row.temperature + '<br>';
                     layer.bindPopup(popup);
                },
                "source": {
                    "url": BASE_DIR + "../api/map/geojson/cty_fill_2013_05/"
                },
            }
        },
    ],
    "initExtent": {
        "x": -122.67419815,
        "y": 45.5284787580,
        "zoom": 11
    }
};

$('.input-daterange').datepicker({
    "format": "yyyy-mm-dd",
    "endDate": Date(),
    "todayBtn": "linked",
    "todayHighlight": true
});

$('.input-daterange .input-sm').datepicker('update', new Date('2014-04-01 00:00:00 PDT'));


$('.input-group.date').datepicker({
    "format": "yyyy-mm-dd",
    "endDate": Date(),
    "todayBtn": "linked",
    "todayHighlight": true
});


var timepickerOpts = {
    "minuteStep": 15,
    "showInputs": false,
    "disableFocus": true,
    "showMeridian": false,
    "showWidgetOnAddonClick": true
};

$('[name=start-time]').timepicker(timepickerOpts);
$('[name=end-time]').timepicker(timepickerOpts);

$('[name=start-time]').timepicker('setTime', '00:00');
$('[name=end-time]').timepicker('setTime', '23:59');


var downloadOpts = {
    "selectors": [
        "start",
        "end",
        "start-time",
        "end-time",
        "deq-measure",
        "weather-measure"
    ],
    "button": null,
    "url": null,
    "fname": null
};

downloadOpts.button = "#download-deq-button";
downloadOpts.url = BASE_DIR + "../api/deq/download";
downloadOpts.fname = "deq_data.csv";

OBDownloads.enableButton(downloadOpts);

downloadOpts.button = "#download-weather-button";
downloadOpts.url = BASE_DIR + "../api/weather/download";
downloadOpts.fname = "weather_data.csv";

OBDownloads.enableButton(downloadOpts);

$(function( ) {
    obMap.addMap(map1);
    $('[data-toggle=tooltip]').tooltip();
}
);