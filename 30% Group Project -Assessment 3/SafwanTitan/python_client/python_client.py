import time
import mysql.connector

def update_points():
    conn = mysql.connector.connect(
        host="mysql",
        user="school_admin",
        password="admin123",
        database="school_db"
    )
    cursor = conn.cursor()

    while True:
        cursor.execute("UPDATE users SET points = points + 3 WHERE role = 'admin'")
        conn.commit()
        print("Admin points updated by client.")
        time.sleep(20)

if __name__ == "__main__":
    update_points()
