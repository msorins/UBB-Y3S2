package service;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class ServiceTest {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void addStudent() throws Exception{
        assertEquals(1, 2);
        throw new Exception("hello");
    }
}