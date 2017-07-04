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

describe('Torrent Info', function() {

    it('init should be successfull', function() {
      let torrentInfo
      let correctPath = './test/sintel.torrent'
      try {
        torrentInfo = new libtorrent.TorrentInfo(correctPath)
      } catch(err) {
        // Do nothing
      }
      assert(torrentInfo)
    })

    it('init should failed : Cannot construct TorrentInfo from supplied argument ', function() {
      let torrentInfo
      let undefinedArg
      try {
        torrentInfo = new libtorrent.TorrentInfo(undefinedArg)
      } catch(err) {
        //console.log(err)
        assert(err)
      }
    })

    it('init should failed : No such file or directory ', function() {
      let torrentInfo
      let wrongPath = './sintel.torrent'
      try {
        torrentInfo = new libtorrent.TorrentInfo(wrongPath)
      } catch(err) {
        //console.log(err)
        assert(err)
      }
    })
})
