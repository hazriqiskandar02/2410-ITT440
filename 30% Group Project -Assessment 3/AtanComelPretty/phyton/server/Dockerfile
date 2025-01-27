FROM python:latest

# Install mysql-connector-python
RUN pip install --default-timeout=300 mysql-connector-python

# Run the server.py script
CMD ["python3", "server.py"]

CMD ["tail", "-f", "/dev/null"]
