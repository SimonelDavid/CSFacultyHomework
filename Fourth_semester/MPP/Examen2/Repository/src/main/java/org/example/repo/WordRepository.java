package org.example.repo;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.domain.User;
import org.example.domain.Word;
import org.springframework.stereotype.Component;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component
public class WordRepository implements IWordRepository {

        private final JdbcUtils dbUtils;
        private static final Logger logger = LogManager.getLogger();

        public WordRepository(){
            Properties props=new Properties();
            try {
                props.load(new FileReader("server.properties"));
                System.out.println(props);
            } catch (IOException e) {
                System.out.println("Cannot find server.properties "+e);
                System.out.println(new File(".").getAbsolutePath());
            }
            dbUtils = new JdbcUtils(props);
        }
        public WordRepository(Properties props) {
            logger.info("Initializing org.example.repo.UserRepository with properties: {} ", props);
            dbUtils = new JdbcUtils(props);
        }
        @Override
        public Word add(Word entity) { return null;}

        @Override
        public void remove(Integer id) {
        }

        @Override
        public void update(Word entity) throws Exception {
        }


        @Override
        public Word getById(int id) { return null;
        }

        @Override
        public Iterable<Word> getAll() {
            String sql = "SELECT * FROM \"Words\"";
            logger.traceEntry("finding all words");
            Connection con= dbUtils.getConnection();
            List<Word> entities = new ArrayList<>();
            try(PreparedStatement ps = con.prepareStatement(sql)) {
                try(ResultSet rs = ps.executeQuery()) {
                    while(rs.next()) {
                        int idd = rs.getInt("id");
                        String word = rs.getString("word");
                        Word entity = new Word(word);
                        entity.setId(idd);
                        entities.add(entity);
                    }
                }
            } catch (SQLException e) {
                logger.error(e);
                System.err.println("Error DB " + e);
            }
            logger.traceExit(entities);
            return entities;
        }

        @Override
        public int sizee() {
            List<Word> all= (List<Word>)getAll();
            return all.size();
        }
}
