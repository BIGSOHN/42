FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/setup-ssl.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/setup-ssl.sh

RUN /usr/local/bin/setup-ssl.sh

CMD ["nginx", "-g", "daemon off;"]
