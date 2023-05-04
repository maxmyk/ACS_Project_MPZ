import psycopg2


class ConnectionDB:

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.conn = psycopg2.connect(
                host="localhost",
                port=5432,
                database="postgres",
                user="postgres",
                password="acs"
            )
        return cls._instance

    def __init__(self):
        self.cursor = self.conn.cursor()
        self._execute_query("""CREATE TABLE IF NOT EXISTS data (
                id INTEGER,
                temperature FlOAT,
                humidity FLOAT,
                timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP);""")

    async def add_value(self, key, value):
        self._execute_query(f"INSERT INTO data (id, temperature, humidity)\
         VALUES ({key}, {value['temperature']}, {value['humidity']})")

    async def get_last_value(self, key):
        data = self._execute_query(f"SELECT temperature, humidity FROM data WHERE id = {key} ORDER BY timestamp DESC LIMIT 1")
        return {"temperature": data[0][0], "humidity": data[0][1]}

    def _execute_query(self, query):
        self.cursor.execute(query)
        if query.startswith("SELECT"):
            try:
                return self.cursor.fetchall()
            except Exception:
                return [(0, 0, 0)]

        else:
            self.conn.commit()

    def close_connection(self):
        self.conn.close()

