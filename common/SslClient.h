#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/certs.h"
#include "mbedtls/x509.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"
#include "mbedtls/timing.h"

#include "DefaultConfig.h"
#include "MbedException.cpp"

class SslClient
{
public:
	SslClient();
	~SslClient();
	void InitRng();
	void LoadTrustedCerts(Options);
	void LoadClientKeys(Options);
	void StartConnection(Options);
	void SetupStuff(Options, const char**, unsigned char*, size_t);
	void PerformHandshake(Options);
	void VerifyServerCert(Options);
	void SendGet(Options);
	void ReadResponse(Options);
	void ReuseConnection(Options);
	void CloseConnection();
	void Reconnect(Options);
 	unsigned char buf[MBEDTLS_SSL_MAX_CONTENT_LEN + 1];	
	mbedtls_ssl_context ssl;
	int retry_left;

private:
	const char *pers = "ssl_client2";
    mbedtls_net_context server_fd;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_config conf;
    mbedtls_ssl_session saved_session;
#if defined(MBEDTLS_TIMING_C)
    mbedtls_timing_delay_context timer;
#endif
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    uint32_t flags;
    mbedtls_x509_crt cacert;
    mbedtls_x509_crt clicert;
    mbedtls_pk_context pkey;
#endif
    int ret;
	
};
