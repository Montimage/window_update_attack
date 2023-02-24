# Use an official image as the base image
FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y make gcc libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory in the container
WORKDIR /app

# Copy the client files into the container
COPY /src .

# Set environment variables to allow the client to connect to the server running on localhost at port 8000
ENV port=8000
ENV ip=localhost
ENV reqNumber=100000

ENV API_HOST=host.docker.internal
# Install the necessary tools for building and running the client


# Compile the client code
RUN make



# Start the client
CMD ./main_curl ${ip} ${port} ${reqNumber} 
