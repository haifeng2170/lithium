
namespace iod {

  std::string generate_secret_tracking_id()
  {
    std::ostringstream os;
    std::random_device rd;
    os << std::hex << rd() << rd() << rd() << rd();
    return os.str();
  }
  
  inline std::string session_cookie(http_request& request,
				    http_request& response,
				    const char* key = "silicon_token")
  {
    std::string token;
    const char* token_ = MHD_lookup_connection_value(request.mhd_connection, MHD_COOKIE_KIND, key.c_str());

    if (!token_)
      {
        token = generate_secret_tracking_id();
        response.set_cookie(key, token);
      }
    else
      {
        token = token_;
      }

    return token;
  }

}