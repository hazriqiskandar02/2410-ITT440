# Use an official Python image
FROM python:3.9-slim

# Set the working directory
WORKDIR /app

# Copy the Python client code into the container
COPY python_client.py .

# Install necessary Python packages
RUN pip install mysql-connector-python

# Command to run the Python client
CMD ["python", "python_client.py"]