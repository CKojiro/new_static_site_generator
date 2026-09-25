
const fs = require('fs');
const http = require('http');

const PORT = 8888;

const server = http.createServer((req, res) =>
{
    if (req.url === '/')
    {
        fs.readFile('./index.html', (err, data) =>
        {
            if (err)
            {
                res.writeHead(500);
                res.end('Error loading HTML file');
                return;
            }

            res.writeHead(200, {'Content-Type': 'text/html'});
            res.end(data);
        });
    }
    else if (req.url === '/styles.css')
    {
        fs.readFile('./styles.css', (err, data) =>
        {
            if (err)
            {
                res.writeHead(500);
                res.end('Error loading CSS file');
                return;
            }

            res.writeHead(200, {'Content-Type': 'text/css'});
            res.end(data);
        });
    }
    else
    {
        res.writeHead(404);
        res.end('Not found');
    }
});

server.listen(PORT, () =>
{
    console.log(`Server is running at http://localhost:${PORT}/`);
});
