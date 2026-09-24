
const http = require('http');

const PORT = 8888;

const server = http.createServer((req, res) =>
{
    res.writeHead(200, {'Content-Type': 'text/plain'});

    res.end('Hello! Your local JavaScript server is running successfully.\n');
});

server.listen(PORT, () =>
{
    console.log(`Server is running at http://localhost:${PORT}/`);
});
