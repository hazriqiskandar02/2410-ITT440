import os
import time
import threading
import socket
import mysql.connector
import datetime

DB_HOST = os.environ.get('DB_HOST', 'localhost')
DB_USER = os.environ.get('DB_USER', 'testuser')
DB_PASS = os.environ.get('DB_PASS', 'secret')
DB_NAME = os.environ.get('DB_NAME', 'testdb')
DB_PORT = int(os.environ.get('DB_PORT', '3306'))

def connect_db():
    return mysql.connector.connect(
        host=DB_HOST,
        user=DB_USER,
        password=DB_PASS,
        database=DB_NAME,
        port=DB_PORT
    )

def updater():
    while True:
        conn = connect_db()
        cursor = conn.cursor()
        sql = """
        INSERT INTO users_points (user, points, datetime_stamp)
        VALUES ('UserPy', 5, NOW())
        ON DUPLICATE KEY UPDATE
          points = points + 5,
          datetime_stamp = NOW()
        """
        try:
            cursor.execute(sql)
            conn.commit()
        except Exception as e:
            print(f"[{datetime.datetime.now().strftime('%H:%M:%S')}] Update failed: {e}", flush=True)
        cursor.close()
        conn.close()
        time.sleep(5)

def get_points():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("SELECT points FROM users_points WHERE user='UserPy'")
    row = cursor.fetchone()
    points = row[0] if row else -1
    cursor.close()
    conn.close()
    return points

def handle_client(client_socket):
    # Connection timestamp
    conn_time = datetime.datetime.now().strftime('[%H:%M:%S]')
    print(f"{conn_time} New client connection", flush=True)
    
    data = client_socket.recv(1024).decode('utf-8').strip()
    
    if data == "GET":
        # Request processing timestamp
        process_time = datetime.datetime.now().strftime('[%H:%M:%S]')
        print(f"{process_time} Processing GET request", flush=True)
        
        pts = get_points()
        msg = f"Points for UserPy: {pts}\n"
        client_socket.sendall(msg.encode('utf-8'))
    else:
        # Unknown command timestamp
        error_time = datetime.datetime.now().strftime('[%H:%M:%S]')
        print(f"{error_time} Received invalid command: {data}", flush=True)
        client_socket.sendall(b"Unknown command\n")
        
    client_socket.close()

def main():
    # Start background thread for DB updates
    t = threading.Thread(target=updater, daemon=True)
    t.start()

    # Create TCP server on port 2002
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 2002))
    server_socket.listen(5)
    
    # Server startup timestamp
    start_time = datetime.datetime.now().strftime('[%H:%M:%S]')
    print(f"{start_time} Python Server listening on port 2002...", flush=True)

    while True:
        client, addr = server_socket.accept()
        handle_client(client)

if __name__ == "__main__":
    main()
