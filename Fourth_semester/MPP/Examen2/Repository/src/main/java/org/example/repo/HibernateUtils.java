package org.example.repo;

import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

public class HibernateUtils
{
    private static SessionFactory sessionFactory;

    public static SessionFactory getSessionFactory()
    {
        if (sessionFactory == null)
        {
            initialize();
        }

        return sessionFactory;
    }

    public static void close()
    {
        if (sessionFactory != null)
        {
            sessionFactory.close();
        }
    }

    private static void initialize()
    {
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder().configure().build();
        try
        {
            sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        }
        catch (Exception exception)
        {
            System.err.println("Session factory initialization exception " + exception);
            exception.printStackTrace();
            StandardServiceRegistryBuilder.destroy(registry);
        }
    }
}