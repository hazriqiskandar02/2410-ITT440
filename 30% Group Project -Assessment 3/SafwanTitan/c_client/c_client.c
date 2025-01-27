#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>

void update_points() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "mysql", "school_admin", "admin123", "school_db", 3306, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        exit(1);
    }

    while (1) {
        if (mysql_query(conn, "UPDATE users SET points = points + 2 WHERE role = 'teacher'")) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        } else {
            printf("Teacher points updated.\n");
        }
        sleep(20);
    }

    mysql_close(conn);
}

int main() {
    update_points();
    return 0;
}
