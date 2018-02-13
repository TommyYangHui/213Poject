#ifndef _ACCESS_TOKEN_H
#define _ACCESS_TOKEN_H


int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK);
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream);

#endif



