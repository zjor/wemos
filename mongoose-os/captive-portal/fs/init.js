load('api_net.js');
load("api_file.js");

let pageContent = File.read('index.html');

Net.serve({
  addr: 'tcp://80',
  ondata: function(conn, data) {
    Net.send(conn, 'HTTP/1.1 200 OK\n');
    Net.send(conn, 'Content-Type: text/html\n');
    Net.send(conn, 'Connection: Closed\n\n');
    Net.send(conn, pageContent);
    Net.discard(conn, data.length);
    Net.close(conn);
  }
});

print('Server started at tcp://80');