FROM gcc:latest
WORKDIR /app
COPY c_client.c .
RUN gcc c_client.c -o c_client -lmysqlclient
CMD ["./c_client"]
