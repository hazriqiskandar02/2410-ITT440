# Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
    apt-get install -y build-essential libmysqlclient-dev mysql-client && \
    apt-get clean

# Set the working directory
WORKDIR /app

# Copy the C server code into the container
COPY c_server1.c .

# Compile the C server code
RUN gcc -o c_server1 c_server1.c -lmysqlclient

# Command to run the compiled C server
CMD ["./c_server1"]