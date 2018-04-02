var libtorrent = require('../')
var assert = require('assert');

describe('libtorrent addon', function (done) {
    it('can create a session and pop alerts', function () {
      const listenPort = 6060

      let session = new libtorrent.Session({
        listen_interfaces: '0.0.0.0:' + listenPort,
        enable_dht: false,
        allow_multiple_connections_per_ip: false
      })

      assert(session.listenPort(), listenPort)

      var alerts = session.popAlerts()

      for (let i in alerts) {
        console.log(alerts[i].message)
      }

      setTimeout(function () {
        done()
      }, 4000)
    })
})

describe('Torrent Info', function() {

    it('init should be successfull', function() {
      let torrentInfo
      let correctPath = './test/sintel.torrent'
      try {
        torrentInfo = new libtorrent.TorrentInfo(correctPath)
      } catch(err) {
        assert(false)
        return
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
        return
      }
      assert(false)
    })

    it('init should failed : No such file or directory ', function() {
      let torrentInfo
      let wrongPath = './sintel.torrent'
      try {
        torrentInfo = new libtorrent.TorrentInfo(wrongPath)
      } catch(err) {
        //console.log(err)
        assert(err)
        return
      }
      assert(false)
    })
})
