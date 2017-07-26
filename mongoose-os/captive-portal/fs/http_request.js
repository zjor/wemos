let HttpRequest = {
	parse: function(req) {
		let lines = req.split(/\r?\n/);
		let first = lines.shift().split(/\s/);
		let http = {
			method: first[0].toLowerCase(),
			uri: first[1],
			version: first[2],
			headers: []
		};

		while (lines.length > 0 && lines[0].length > 0) {
			let header = lines.shift().split(':');

			http.headers.push({
				key: header[0],
				value: header[1].trim()
			});
		}

		return http;
	}
};

// 'use strict';

// let req = "GET / HTTP/1.1\x0d\x0aHost: google.com:8080\x0d\x0aConnection: keep-alive\x0d\x0aAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\x0d\x0aUser-Agent: Mozilla/5.0 (Linux; U; Android 4.4.4; en-us; GT-I9305 Build/KTU84P) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30\x0d\x0aAccept-Encoding: gzip,deflate\x0d\x0aAccept-Language: en-US\x0d\x0aAccept-Charset: utf-8, iso-8859-1, utf-16, *;q=0.7\x0d\x0aCookie: SID=NQNYxWLT0Dz2NL-n4F-1-4djMReNG0IIAE-qzE-NYBTrB2E-pn3FGRXoc-gxIBeX-NJBtg.; HSID=APOWIC3lmoN_gbA2y; APISID=Qzfdi3mgRkCEYX7f/AjOqBCcyKY3FIcTX7; NID=103=cdH7R5Slc60Iy-pj4IVoq-ksDbe0AOMggUsxP9I7CqRCxc8xoxRgd0-jMXLtJqW2kyZQ2e3Soo9napVsI-YL8Y7rQoVZ2JBwrhEF2jBEhVLzaKjJt7qqZc0C4d8SsENUdB-DyT4WNXlX_B20bN6aUDHGrr62GsToJW415NPcJ8sUIsFHkO2UnrURgBYocCquith5B2Wf8UJM5qRepwOOg7EcxAaLRiqyIIVBGWT1jDR7kAcae9-l8qVnlzwHtbXqUyKI1qEMf1egAtQdQ5qS8nqaqljhhHVIlA\x0d\x0a\x0d\x0a"

// function parseHttpRequest(req) {
// 	let lines = req.split(/\r?\n/);
// 	let first = lines.shift().split(/\s/);
// 	let http = {
// 		method: first[0].toLowerCase(),
// 		uri: first[1],
// 		version: first[2],
// 		headers: []
// 	};

// 	while (lines.length > 0 && lines[0].length > 0) {
// 		let header = lines.shift().split(':');

// 		http.headers.push({
// 			key: header[0],
// 			value: header[1].trim()
// 		});
// 	}

// 	return http;
// }

// console.log(parseHttpRequest(req));


