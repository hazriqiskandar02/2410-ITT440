FROM mysql:latest

# Set environment variables for MySQL
ENV MYSQL_ROOT_PASSWORD=rootpassword
ENV MYSQL_DATABASE=school_db
ENV MYSQL_USER=school_admin
ENV MYSQL_PASSWORD=admin123

# Copy initialization SQL scripts to Docker's entrypoint directory
COPY init.sql /docker-entrypoint-initdb.d/

# Expose the default MySQL port
EXPOSE 3306
