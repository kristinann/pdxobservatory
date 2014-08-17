    <!-- Main container -->
    <div class="container">
      <!-- Map and selectors -->
      <div class="row">
        <!-- Map -->
        <div class="col-md-8 widget">
          <div class="map-div" id="mapdiv1"></div>
        </div>

        <!-- Selectors and buttons -->
        <div class="col-md-4 widget">
          <form class="form-horizontal" role="form" id="selectors">
            <div class="form-group" id="date-range-group">
              <label class="col-sm-4" for="start">Date range</label>
              <div class="col-sm-8 input-daterange input-group" id="datepicker">
                <input type="text" class="input-sm form-control" name="start">
                <span class="input-group-addon">to</span>
                <input type="text" class="input-sm form-control" name="end">
              </div>
            </div>
            <div class="form-group" id="time-range-group">
              <label class="col-sm-4" for"start-time">Start time</label>
              <div class="col-sm-8 input-timepicker input-group bootstrap-timepicker">
                <span class="input-group-addon input-sm"><span class="glyphicon glyphicon-time"></span></span>
                <input type="text" class="input-sm form-control" name="start-time">
                <span class="input-group-addon">to</span>
                <input type="text" class="input-sm form-control" name="end-time">
                <span class="input-group-addon input-sm"><span class="glyphicon glyphicon-time"></span></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="deq-measure-group">
              <hr>
              <label class="col-sm-4" for="deq-measure">DEQ Measure</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="deq-measure">
                  <option value="barometric_pressure">Barometric Pressure</option>
                  <option value="carbon_monoxide">Carbon Monoxide</option>
                  <option value="delta_temperature">Delta Temperature</option>
                  <option value="light_scatter">Light Scatter</option>
                  <option value="lower_level_temperature">Lower Level Temperature</option>
                  <option value="middle_level_temperature">Middle Level Temperature</option>
                  <option value="nitric_oxide">Nitric Oxide</option>
                  <option value="nitrogen_dioxide">Nitrogen Dioxide</option>
                  <option value="nitrogen_oxides" selected>Nitrogen Oxides</option>
                  <option value="ozone">Ozone</option>
                  <option value="relative_humidity">Relative Humidity</option>
                  <option value="resultant_direction">Resultant Direction</option>
                  <option value="resultant_speed">Resultant Speed</option>
                  <option value="solar_radiation">Solar Radiation</option>
                  <option value="sulfur_dioxide">Sulfur Dioxide</option>
                  <option value="temperature">Temperature</option>
                  <option value="upper_level_temp">Upper Level Temperature</option>
                  <option value="wind_speed">Wind Speed</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="weather-measure-group">
              <hr>
              <label class="col-sm-4" for="weather-measure">Weather Measure</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="weather-measure">
                  <option value="temp_c" selected>Average Temperature</option>
                  <option value="precip_1hr_metric">Total Precipitation</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback disabled" id="bt-measure-group">
              <hr>
              <label class="col-sm-4" for="bt-measure">Travel Time</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" disabled name="bt-measure">
                  <option value="pct_avg_tt">Percent of Expected Travel Time</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="transit-measure-group">
              <hr>
              <label class="col-sm-4" for="transit-measure">Transit Measure</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="transit-measure">
                  <option value="on_time" selected>Stop Performance</option>
                  <option value="stop_activity">Stop Activity</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="timeofday-group">
              <label class="col-sm-4" for="timeofday">Time of Day</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="timeofday">
                  <option value="Early AM">Early AM</option>
                  <option value="AM Peak" selected>AM Peak</option>
                  <option value="Morning">Morning</option>
                  <option value="Midday">Midday</option>
                  <option value="PM Peak">PM Peak</option>
                  <option value="Night">Night</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="service-key-group">
              <label class="col-sm-4" for="service-key">Service Type</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="service-key">
                  <option value="W" selected>Weekday</option>
                  <option value="S">Saturday</option>
                  <option value="U">Sunday</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div>
            <div class="form-group has-feedback" id="guide-selection-group">
              <hr>
              <label class="col-sm-4" for="guide_selection">Guides</label>
              <div class="col-sm-8">
                <select class="form-control input-sm btn-sm" name="guide_selection">
                  <option value="0">Select a Guide</option>
                </select>
                <span class="glyphicon glyphicon-plus form-control-feedback"></span>
              </div>
            </div> 
            <div class="form-group has-feedback" id="guide-slidebar-group">
              <label class="col-sm-4">Hour</label>
              <div class="col-sm-8">
                  <table width="100%"><tr><td><div id="guide_hour_slider"></div></td><td width="50" align="right"><div id="guide_hour_text" style="width:40px;">00:00</div></td></tr></table> 
              </div>
            </div>    
            <div class="row form-group" id="guide-edit-group">
              <div class="col-sm-8 col-sm-offset-4">
                <a class="form-control input-sm btn btn-primary btn-sm" data-toggle="modal" onclick="guide.edit();">Edit Guide<span class="pull-right glyphicon glyphicon-glass"></span></a>
              </div>
            </div>
            <div class="row form-group" id="make-guide-group">
              <div class="col-sm-8 col-sm-offset-4">
                <a class="form-control input-sm btn btn-primary btn-sm" data-toggle="modal" onclick="guide.new();">Create Guide<span class="pull-right glyphicon glyphicon-glass"></span></a>
              </div>
            </div>
          </form>
          <div class="row form-group" id="update-group">
            <hr>
            <div class="col-sm-4"></div>
            <div class="col-sm-8">
              <a class="form-control btn btn-sm btn-default input-sm disabled" id="update-button">Update<span class="pull-right glyphicon glyphicon-refresh"></span></a>
            </div>
          </div>
          <div class="row form-group" id="download-deq-group">
            <div class="col-sm-8 col-sm-offset-4">
              <a class="form-control btn btn-sm btn-default input-sm" role="button" id="download-deq-button">Download DEQ data<span class="pull-right glyphicon glyphicon-floppy-save"></span></a>
            </div>
          </div>
          <div class="row form-group" id="download-weather-group">
            <div class="col-sm-8 col-sm-offset-4">
              <a class="form-control btn btn-sm btn-default input-sm" id="download-weather-button">Download weather data<span class="pull-right glyphicon glyphicon-floppy-save"></span></a>
            </div>
          </div>
          <div class="row form-group" id="download-volume-report-group">
            <div class="col-sm-8 col-sm-offset-4">
              <a class="form-control btn btn-sm btn-default input-sm" data-toggle="modal" data-target="#volume-report-modal">Download Volume Excel Report<span class="pull-right glyphicon glyphicon-floppy-save"></span></a>
            </div>
          </div>
          <div class="row form-group" id="download-speed-report-group">
            <div class="col-sm-8 col-sm-offset-4">
              <a class="form-control btn btn-sm btn-default input-sm" data-toggle="modal" data-target="#speed-report-modal">Download Speed Excel Report<span class="pull-right glyphicon glyphicon-floppy-save"></span></a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Modal dialog for guide creation -->
    <div class="modal fade" id="guide-modal" tabindex="-1" role="dialog" aria-labelledby="guide-header" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
            <h4 class="modal-title" id="guide-header">Create Guide</h4>
          </div>
          <div class="modal-body">
            <form class="form-horizontal" role="form" id="guide-form">
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="guide-name">Perspective</label>
                <div class="col-sm-8">
                    <select class="form-control input-sm required" name="guide-type">
                      <optgroup label="Traffic">
                        <option value="traffic-speed">Speed</option>
                        <option value="traffic-volume">Volume</option>
                      </optgroup>
                      <optgroup label="Weather">
                        <option value="weather-temp">Temperature</option>
                      </optgroup>
                    </select>
                    <span class="glyphicon glyphicon-plus  form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="guide-name">Guide Name</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Specify a name for the guide." name="guide-name">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="guide-description">Description</label>
                <div class="col-sm-8">
                  <textarea class="form-control required" id="guide-description" name="guide-description" data-toggle="tooltip" data-placement="bottom" title="Enter a description for this guide." rows="4"></textarea>
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback" id="guide-year-group">
                <label class="col-sm-4 control-label" for="guide-year">Year</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Specify a year for the guide." name="guide-year">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback" id="guide-date-group">
                <label class="col-sm-4 control-label" for="guide-date">Date</label>
                <div class="col-sm-8 input-group date">
                    <input type="text" class="form-control input-sm required" data-date-format="yyyy-mm-dd" name="guide-date"><span class="input-group-addon"><i class="glyphicon glyphicon-th"></i></span>
                </div>
              </div>
              <div class="form-group" id="guide-time-range-group">
                <label class="col-sm-4 control-label" for="guide-start-time">Start time</label>
                <div class="input-timepicker input-group bootstrap-timepicker col-sm-8">
                  <span class="input-group-addon input-sm"><span class="glyphicon glyphicon-time"></span></span>
                  <input type="text" class="input-sm form-control" name="guide-start-time">
                  <span class="input-group-addon">to</span>
                  <input type="text" class="input-sm form-control" name="guide-end-time">
                  <span class="input-group-addon input-sm"><span class="glyphicon glyphicon-time"></span></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="guide-region">Region</label>
                <div class="col-sm-4">
                  <div class="radio">
                    <label><input type="radio" checked name="guide-region" value="portland">Portland</label>
                  </div>
                </div>
                <div class="col-sm-4">
                  <div class="radio">
                    <label><input type="radio" name="guide-region" value="vancouver">Vancouver</label>
                  </div>
                </div>
              </div>
              <div class="row form-group" id="guide-layers">
                <label class="col-sm-4 control-label">Display Layers</label>
                <div class="col-sm-4">
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-vegetation" value="layer-vegetation"> Vegetation
                    </label>
                  </div>
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-school-sites" value="layer-school-sites"> School Sites
                    </label>
                  </div>
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-counties" value="layer-counties"> Counties
                    </label>
                  </div>
                </div>
                <div class="col-sm-4">
                <!--
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-taxlots" value="layer-taxlots"> Taxlots
                    </label>
                  </div>
                -->
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-parking-meters" value="layer-parking"> Parking Meters
                    </label>
                  </div>
                  <div class="checkbox">
                    <label>
                      <input type="checkbox" name="layer-bicycle-routes" value="layer-bicycle-routes"> Bicycle Routes
                    </label>
                  </div>
                </div>
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default"  data-dismiss="modal">Cancel</button>
            <button type="button" class="btn btn-primary" id="guide-save" onclick="guide.doEdit();">Save Guide</button>
            <button type="button" class="btn btn-primary" id="guide-create-new" onclick="guide.doAdd();">Create New Guide</button>
          </div>
        </div>
      </div>
    </div>
  
    <!-- Modal dialog for downloading the volume excel report -->
    <div class="modal fade" id="volume-report-modal" tabindex="-1" role="dialog" aria-labelledby="volume-report-header" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
            <h4 class="modal-title" id="volume-report-header">Download Volume Excel Report</h4>
          </div>
          <div class="modal-body">
            <form class="form-horizontal" role="form" id="volume-report-form" method="GET" action="http://haystack.cs.pdx.edu/dev/connectportland/reports/traffic-volume-report.php">
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="years">Report Years</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Enter a comma-separated list of years" name="years">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default"  data-dismiss="modal">Cancel</button>
            <button type="button" class="btn btn-primary" id="volume-report-download-button">Download Report</button>
          </div>
        </div>
      </div>
    </div>
    
    <!-- Modal dialog for downloading the speed excel report -->
    <div class="modal fade" id="speed-report-modal" tabindex="-1" role="dialog" aria-labelledby="speed-report-header" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
            <h4 class="modal-title" id="speed-report-header">Download Speed Excel Report</h4>
          </div>
          <div class="modal-body">
            <form class="form-horizontal" role="form" id="speed-report-form" method="GET" action="http://haystack.cs.pdx.edu/dev/connectportland/reports/traffic-speed-report.php">
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="years">Report Years</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Enter a comma-separated list of years" name="years">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default"  data-dismiss="modal">Cancel</button>
            <button type="button" class="btn btn-primary" id="speed-report-download-button">Download Report</button>
          </div>
        </div>
      </div>
    </div>
    
    <!-- Modal dialog for comments -->
    <div class="modal fade" id="comment-modal" tabindex="-1" role="dialog" aria-labelledby="comment-header" aria-hidden="true">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
            <h4 class="modal-title" id="comment-header">Comment</h4>
          </div>
          <div class="modal-body">
            <form class="form-horizontal" role="form" id="comment-form">
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="commenter-name">Commenter</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Please provide your name." name="commenter-name">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="commenter-title">Comment title</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" title="Please enter a comment title." name="comment-title">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="comment-lonlat">Comment location</label>
                <div class="col-sm-8">
                  <input type="text" class="form-control input-sm required" data-toggle="tooltip" data-placement="bottom" disabled title="The x,y coordinate pair for the comment." name="comment-lonlat" placeholder="This comment has no point.">
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group has-feedback">
                <label class="col-sm-4 control-label" for="comment-text">Comment</label>
                <div class="col-sm-8">
                  <textarea class="form-control required" name="comment-text" data-toggle="tooltip" data-placement="bottom" title="Enter your comment." rows="4"></textarea>
                  <span class="glyphicon form-control-feedback"></span>
                </div>
              </div>
              <div class="row form-group" id="comment-layers">
                <label class="col-sm-4 control-label">Layers</label>
                <div class="col-sm-4">
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="vegetation"> Vegetation
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="school-sites"> School Sites
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="counties"> Counties
                    </label>
                  </div>
                  <!--
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="taxlots"> Taxlots
                    </label>
                  </div>
                  -->
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="bluetooth"> Travel Time
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="none" checked> No Layer
                    </label>
                  </div>
                </div>
                <div class="col-sm-4">
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="busstops"> Transite
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="deq"> Air Quality
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="weather"> Weather
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="parking-meters"> Parking Meters
                    </label>
                  </div>
                  <div class="radio">
                    <label>
                      <input type="radio" name="comment-layer" value="bicycle-routes"> Bicycle Routes
                    </label>
                  </div>
                </div>
              </div>
            </form>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
            <button type="button" class="btn btn-primary" id="comment-save">Save Comment</button>
          </div>
        </div>
      </div>
    </div>