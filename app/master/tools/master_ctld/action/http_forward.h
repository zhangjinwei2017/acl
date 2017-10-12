#pragma once

template<typename TReq, typename TRes>
int http_forward(const char* addr, acl::json& in, acl::string& out)
{
	TReq req;
	TRes res;

	if (deserialize<TReq>(in, req) == false)
	{
		logger_error("invalid json=%s", in.to_string().c_str());
		return 400;
	}

	acl::string body;
	serialize<TReq>(req, body);

	acl::http_request conn(addr, 30, 30);
	acl::string url;
	url.format("/?cmd=%s", req.cmd.c_str());
	conn.request_header().set_url(url).set_keep_alive(false)
		.set_content_type("text/json");

	if (conn.request(body, body.size()) == false)
	{
		logger_error("request error, json=[%s]", body.c_str());
		return 503;
	}

	acl::json json;
	if (conn.get_body(json) == false)
	{
		logger_error("get_body error, json=[%s]", body.c_str());
		return 503;
	}

	logger(">>>url=%s, req=|%s|, res=|%s|<<<",
		url.c_str(), body.c_str(), json.to_string().c_str());
#if 1
	out = json.to_string();
	return 200;
#else
	if (deserialize<TRes>(json, res) == false)
	{
		logger_error("deserialize error, res json=[%s], req json=[%s]",
			json.to_string().c_str(), body.c_str());
		return 503;
	}

	serialize<TRes>(res, out);
	return 200;
#endif
}
