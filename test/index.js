var libtorrent = require('../')
var assert = require('assert');

describe('libtorrent addon', function() {

    it('can create a session and pop alerts', function(){
      let session = new libtorrent.Session()

      var alerts = session.popAlerts()

      for (var i in alerts) {
        console.log(alerts[i])
      }
    })
})

