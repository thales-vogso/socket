FROM centos
WORKDIR /data/server
COPY . .
RUN set -ex \
    && yum -y install gcc-c++ make \
    && cd /data/server/src \
    && make 