package unitTest;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class isValidUnitTest {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
	
	@Test
	public void testIsValid() {
		customUnitTestOne();
		customUnitTestTwo();
		customUnitTestThree();
	}
	
	@Test
	public void customUnitTestOne() {
		assertTrue(true);
	}

	@Test
	public void customUnitTestTwo() {
		assertTrue(false);
	}
	
	@Test
	public void customUnitTestThree() {
		assertTrue(true);
	}
}
