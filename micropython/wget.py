import ussl
import usocket

debug = False
warn_ussl = True

def url_open(url):
    global warn_ussl

    if debug:
        print(url)

    proto, _, host, urlpath = url.split('/', 3)
    try:
        ai = usocket.getaddrinfo(host, 443)
    except OSError as e:
        fatal("Unable to resolve %s (no Internet?)" % host, e)
    addr = ai[0][4]

    s = usocket.socket(ai[0][0])
    try:
        s.connect(addr)

        if proto == "https:":
            s = ussl.wrap_socket(s, server_hostname=host)
            if warn_ussl:
                print("Warning: %s SSL certificate is not validated" % host)
                warn_ussl = False

        # MicroPython rawsocket module supports file interface directly
        s.write("GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n" % (urlpath, host))
        l = s.readline()
        protover, status, msg = l.split(None, 2)
        if status != b"200":
            if status == b"404" or status == b"301":
                raise NotFoundError("Package not found")
            raise ValueError(status)
        while 1:
            l = s.readline()
            if not l:
                raise ValueError("Unexpected EOF in HTTP headers")
            if l == b'\r\n':
                break
    except Exception as e:
        s.close()
        raise e

    return s

def get_filename(url):
    return url.split("/")[-1]

def wget(url, target=None):
    if not target:
        target = get_filename(url)
    with open(target, "w") as out:        
        f = url_open(url)
        try:            
            out.write(f.read())
        finally:
            f.close()

if __name__ == "__main__":
    from sys import argv
    if len(argv) == 1 or len(argv) > 3:
        print("Usage: \n\tmicropython wget.py URL [TARGET]\n")
    elif len(argv) == 2:
        wget(argv[1])
    else:
        wget(argv[1], argv[2])


