import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class IsValidUnitTest {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testBasicValidURL() {
		UrlValidator testUrl = new UrlValidator();
		assertTrue(testUrl.isValid("http://google.com"));
		assertTrue(testUrl.isValid("https://www.youtube.com"));
		assertTrue(testUrl.isValid("https://github.com"));
	}
	
	@Test
	public void testBasicInvalidURL() {
		UrlValidator testUrl = new UrlValidator();
		assertFalse(testUrl.isValid("abcdefghijklmnopqrstuvwxyz"));
		assertFalse(testUrl.isValid("test://something.url"));
		assertFalse(testUrl.isValid("thisisn't__\\acorrectURL.com"));
	}
	
	@Test
	public void testSchemes() {
		UrlValidator testUrl = new UrlValidator();
		List schemeList = new ArrayList();
		schemeList.add("http://");
		schemeList.add("ftp://");
		schemeList.add("h3t://");
		for (int i = 0; i < schemeList.size(); i++) {
			System.out.println(schemeList.get(i) + "google.com");
			assertTrue(testUrl.isValid(schemeList.get(i) + "google.com"));
			assertTrue(testUrl.isValid(schemeList.get(i) + "www.youtube.com"));
			assertTrue(testUrl.isValid(schemeList.get(i) + "github.com"));
		}

	}
	

}
