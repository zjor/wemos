#
# This is a picoweb example showing a centralized web page route
# specification (classical Django style).
#
import ure as re
import picoweb

import logging
logging.basicConfig(level=logging.INFO)
#logging.basicConfig(level=logging.DEBUG)

app = picoweb.WebApp(__name__)

@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from app.render_template(resp, "index.html")

@app.route(re.compile("^/static/(.+)"))
def serve_static(req, resp):
	yield from app.sendfile(resp, "static/" + req.url_match.group(1))

@app.route(re.compile("^/iam/(.+)"))
def hello(req, resp):
    yield from picoweb.start_response(resp)
    # Here's how you extract matched groups from a regex URI match
    yield from resp.awrite("Hello " + req.url_match.group(1))

def run():
    
    app.run(host="0.0.0.0", port=7000, debug=True)

if __name__ == "__main__":
    run()    