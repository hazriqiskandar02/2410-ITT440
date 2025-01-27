FROM python:latest

# Install mysql-connector-python
RUN pip install --default-timeout=300 mysql-connector-python

# Run the client.py script
CMD ["python3", "client.py"]

CMD ["tail", "-f", "/dev/null"]
