using System;
using System.Data;
using System.Threading;
using Microsoft.Data.SqlClient;

namespace Lab_04_Rider
{
    internal class Program
    {
        private static string connectionString =
             @"Server=DESKTOP-VCR5GTN\SQLEXPRESS;Database=Bolt_Food;User=DESKTOP-VCR5GTN\simon;Integrated Security=true;TrustServerCertificate=True";

        public static void Main(string[] args)
        {
            ThreadStart deadlock1 = new ThreadStart(T1);
            ThreadStart deadlock2 = new ThreadStart(T2);

            Thread thread1 = new Thread(deadlock1);
            Thread thread2 = new Thread(deadlock2);

            thread1.Start();
            thread2.Start();
        }

        static void T1()
        {
            Deadlock("P1");
        }

        static void T2()
        {
            Deadlock("P2");
        }

        static void Deadlock(string deadlock)
        {
            SqlConnection connection = new SqlConnection(connectionString);
            SqlCommand command = new SqlCommand(deadlock, connection);
            command.CommandType = CommandType.StoredProcedure;
            connection.Open();
            int tries = 3;
            while (tries > 0)
            {
                try
                {
                    Console.WriteLine("Rulam deadlock: " + deadlock);
                    command.ExecuteNonQuery();
                    Console.WriteLine(deadlock + " (deadlock-ul a fost executat cu succes)");
                    tries = -1;
                }
                catch (SqlException ex)
                {
                    Console.WriteLine(deadlock + " " + ex.Message + "\n");
                    tries--;
                }
            }

            if (tries == 0)
            {
                Console.WriteLine(deadlock + " Eroare!");
            }
            connection.Close();
        }
    }
}