var ext = require("./LibtorrentAddon.node");

var session = new ext.Session()

function run(n) {
  n = n || 1

  if(n == 10)
    return process.exit(0);

  var alerts = session.popAlerts()

  for (var i in alerts)
    console.log(alerts[i].message)

  setTimeout(function(){
    run(++n)
  }, 200)
}

run()

