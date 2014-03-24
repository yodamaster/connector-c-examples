/* Copyright (C) 2005, 2006 Hartmut Holzgraefe

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

/*
 * MySQL C client API example: mysql_stmt_field_count()
 *
 * see also http://mysql.com/mysql_stmt_field_count
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql.h>

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;

  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
        
  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
			  MYSQL_HOST,         /* server hostname or IP address */ 
			  MYSQL_USER,         /* mysql user */
			  MYSQL_PWD,          /* password */
			  NULL,               /* default database to use, NULL for none */
			  0,           /* port number, 0 for default */
			  NULL,        /* socket file or named pipe name */
			  CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
  } else {
    MYSQL_STMT *stmt;
    char *query;

    stmt = mysql_stmt_init(mysql);

    if (stmt) {
      puts("Statement init OK!");
    } else {
      printf("Statement init failed: %s\n", mysql_error(mysql));
    }

    if (stmt) {
      query = "SELECT VERSION(), USER()";
                        
      if (mysql_stmt_prepare(stmt, query, strlen(query))) {
	printf("Statement prepare failed: %s\n", mysql_stmt_error(stmt));
      } else {
	puts("Statement prepare OK!");
      }
                        
      if (mysql_stmt_execute(stmt)) {
	printf("Statement execute failed: %s\n", mysql_stmt_error(stmt));
      } else {
	puts("Statement execute OK!");
      }
                        
      printf("The result has %d fields\n", mysql_stmt_field_count(stmt));

      mysql_stmt_free_result(stmt);
      mysql_stmt_close(stmt);
    }
  }
        
  mysql_close(mysql);

  return EXIT_SUCCESS;
}
