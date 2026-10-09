#include <libpq-fe.h>
#include <iostream>

// Minimal PostgreSQL connection test: connect to jerrymusic and run SELECT 1.
int main() {
    const char* conninfo =
        "host=127.0.0.1 port=5432 dbname=jerrymusic user=postgres password=123456";

    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "[FAIL] connection failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }
    std::cout << "[OK] connected to PostgreSQL" << std::endl;

    PGresult* res = PQexec(conn, "SELECT 1 AS ok");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "[FAIL] query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        return 1;
    }
    std::cout << "[OK] SELECT 1 = " << PQgetvalue(res, 0, 0) << std::endl;

    PQclear(res);
    PQfinish(conn);
    return 0;
}
