FROM java:8

ENV ES_PKG_NAME elasticsearch-1.5.0

RUN cd / && \
  wget https://download.elasticsearch.org/elasticsearch/elasticsearch/$ES_PKG_NAME.tar.gz && \
  tar xvzf $ES_PKG_NAME.tar.gz && rm -f $ES_PKG_NAME.tar.gz && mv /$ES_PKG_NAME /elasticsearch

VOLUME ["/data"]

ADD config/elasticsearch.yml /elasticsearch/config/elasticsearch.yml

WORKDIR /data

CMD ["/elasticsearch/bin/elasticsearch"]

# Expose ports.
#   - 9200: HTTP
#   - 9300: transport
EXPOSE 9200
EXPOSE 9300
