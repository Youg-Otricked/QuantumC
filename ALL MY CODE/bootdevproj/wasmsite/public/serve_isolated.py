# save this as serve_isolated.py
import http.server
import socketserver

PORT = 8080

class CORSHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        super().end_headers()

# Change the directory to serve files from
# In a real scenario, you'd navigate to the directory containing your hello.html
# and run this script from there.
Handler = CORSHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving at http://localhost:{PORT}")
    print("Ensure this script is run from the directory containing your hello.html")
    httpd.serve_forever()