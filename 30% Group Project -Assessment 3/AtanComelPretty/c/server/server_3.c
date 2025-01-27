#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <time.h>

void update_database(const char *username) {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "192.168.32.2", "root", "root", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "UPDATE user_points SET points = points + 1, datetime_stamp = NOW() WHERE username = '%s';", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "UPDATE failed: %s\n", mysql_error(conn));
    } else {
        printf("Database updated successfully for user 3: %s\n", username);
    }

    mysql_close(conn);
}

void get_points(const char *username, char *response) {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        strcpy(response, "Error: Unable to initialize MySQL");
        return;
    }

    if (mysql_real_connect(conn, "192.168.32.2", "root", "root", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        strcpy(response, "Error: Unable to connect to MySQL");
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT points FROM user_points WHERE username = '%s';", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT failed: %s\n", mysql_error(conn));
        strcpy(response, "Error: Query execution failed");
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result && mysql_num_rows(result) > 0) {
            MYSQL_ROW row = mysql_fetch_row(result);
            snprintf(response, 256, "User %s has %s points.", username, row[0]);
        } else {
            snprintf(response, 256, "User %s not found.", username);
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    char response[1024];
    socklen_t addr_size;
    time_t last_update_time = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1035);  // Port matching Client 3 (c_client3)
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Server 3 running...\n");

    while (1) {
        // Check if it's time for a periodic update
        time_t current_time = time(NULL);
        if (current_time - last_update_time >= 30) {  // Every 5 seconds
            update_database("Atan_Comel3");
            last_update_time = current_time;
        }

        // Handle client requests
        addr_size = sizeof(client_addr);
        ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer) - 1, MSG_DONTWAIT, (struct sockaddr *)&client_addr, &addr_size);

        if (recv_len > 0) {
            buffer[recv_len] = '\0';  // Null-terminate the buffer
            printf("Received message from client 3: %s\n", buffer);

            if (strncmp(buffer, "GET_POINTS:", 11) == 0) {
                // Handle GET_POINTS request
                char *username = buffer + 11; // Extract the username
                get_points(username, response);
            } else if (strncmp(buffer, "UPDATE:", 7) == 0) {
                // Handle UPDATE request
                char *username = buffer + 7; // Extract the username
                update_database(username);
                strcpy(response, "Updated");
            } else {
                strcpy(response, "Error: Invalid request. Please send 'UPDATE:<username>' or 'GET_POINTS:<username>'.");
            }

            // Send response back to client
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_size);
        }

        // Small sleep to prevent CPU overuse
        usleep(100000);  // 100 ms
    }

    close(sockfd);
    return 0;
}
