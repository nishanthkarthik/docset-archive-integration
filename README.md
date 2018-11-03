# Docset server PoC

To eliminate extracting docsets each time they are downloaded, they are packed instead as `cdb` files.

This can be used to maintain backwards compatibility with `QWebView` in `zeal`

`cdb`, Constant DataBase is a fast, indexed archive (http://www.corpit.ru/mjt/tinycdb.html)

## Instructions

- Download tinycdb, build and modify the path in `docset-server.qbs`
- Build the project with qbs
- Place the sqlite cdb file in the same folder as the built binary
- Run `siege -f urls.txt` to hit our server with the sqlite test urls

## How it works

- The docset is extracted, indexed with `d2cdb` (https://github.com/matthewstory/d2cdb)
- A TCP server listens for the URLs
- For every URL hit, the path is clipped and a lookup is done on the `cdb` file
- If successful, the file contents are retrieved from the `cdb` and converted to HTTP
- The raw HTTP chunk is sent through a TCP server

## File size comparison

- Docset folder after extraction - 24M
- Docset folder as CDB - 22M

## Sample benchmark on `sqlite` docset cdb

```
Lifting the server siege...
Transactions:		       65857 hits
Availability:		       99.84 %
Elapsed time:		       14.89 secs
Data transferred:	      950.36 MB
Response time:		        0.01 secs
Transaction rate:	     4422.90 trans/sec
Throughput:		       63.83 MB/sec
Concurrency:		       24.08
Successful transactions:       65858
Failed transactions:	         103
Longest transaction:	        0.06
Shortest transaction:	        0.00
```
