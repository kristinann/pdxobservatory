window.OBDownloads = {
  "enableButton" : function ( params ) {
    var callback = this.getDLCallback(params);
    $(params.button).on('click',callback);
  },
  "getDLCallback" : function ( params ) {
    var selectors = params.selectors;
    var url = params.url;
    var button = params.button;
    var fname = params.fname;

    var callback = function ( ) {
      var values = '';
      $(selectors).each (
        function ( idx, name ) {
          values += '/' + name + '/' + $('[name=' + name + ']').val()
        }
      );
      $(button).attr('href',url + values);
      $(button).attr('download',fname);
    };
    return callback;
  }
};