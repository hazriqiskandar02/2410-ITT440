# Use an official Python image
FROM python:3.9-slim

# Set the working directory
WORKDIR /app

# Copy the Python server code into the container
COPY python_server1.py .

# Install necessary Python packages
RUN pip install mysql-connector-python

# Command to run the Python server
CMD ["python", "python_server1.py"]