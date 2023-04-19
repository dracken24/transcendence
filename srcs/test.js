let http = require('http');

http.createServer(function (req, res)
{
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end('GO GO POWER RANGER!!!');
})

.listen(8080);
