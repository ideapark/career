const http = require('http');
const fs = require('fs');
const os = require('os');
const dns = require('dns');

const dataFile = "./kubia.txt";
const serviceName = "kubia";
const port = 8080;

var handler = function(request, response) {
    if (request.method == 'POST') {
        var file = fs.createWriteStream(dataFile);
        file.on('open', function(fd) {
            request.pipe(file);
            console.log("New data has been received and stored.");
            response.writeHead(200);
            response.end("Data stored on pod " + os.hostname() + "\n");
        });
    } else {
        response.writeHead(200);
        if (request.url == '/data') {
            var data = fileExists(dataFile)
                ? fs.readFileSync(dataFile, 'utf8')
                : "No data posted yet";
            response.end(data);
        } else {
            response.write("You've hit " + os.hostname() + "\n");
            response.write("Data stored in the cluster: \n");
            dns.resolveSrv(serviceName, function(err, addresses) {
                if (err) {
                    response.end("Could not lookup DNS SRV records: " + err);
                    return;
                }
                var numResponses = 0;
                if (addresses.length == 0) {
                    response.end("No peers discovered.");
                } else {
                    addresses.forEach(function(item) {
                        var requestOptions = {
                            host: item.name,
                            port: port,
                            path: '/data'
                        };
                        httpGet(requestOptions, function(returnedData) {
                            numResponses++;
                            response.write("- " + item.name + ": " + returnedData);
                            response.write("\n");
                            if (numResponses == addresses.length) {
                                response.end();
                            }
                        });
                    });
                }
            });
        }
    }
};

var www = http.createServer(handler);
www.listen(8080);
