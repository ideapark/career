FROM ubuntu:latest

RUN apt-get update && apt-get -y install fortune
ADD fortuneloop /bin/fortuneloop

ENTRYPOINT ["/bin/fortuneloop"]
CMD ["10"]
