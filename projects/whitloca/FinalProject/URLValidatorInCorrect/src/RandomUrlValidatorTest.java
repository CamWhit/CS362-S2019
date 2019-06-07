import static org.junit.Assert.*;

import java.util.Random;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class RandomUrlValidatorTest {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testIsValid() {
		//Create URL object
		UrlValidator testUrl = new UrlValidator();
		
		//Test initial known URL for basic functionality
		assertTrue(testUrl.isValid("http://google.com"));
		//assertTrue(testUrl.isValid("h3t://go.au/t123?action=edit&mode=up"));
		
		//Variable to generate strings
		String testString;
		
		//Variables to keep track of variables in the arrays
		int schemeLoc, authorityLoc, pathLoc, queryLoc;
		
		//Variable to compare whether the generated URL should be valid or invalid
		boolean expectedValidity, actualValidity;
		
		//Set up random generation
		Random rand = new Random();
		
		//Generate random URL string and run through tests
		for (int i = 0; i < 1000000; i++) {
			expectedValidity = true;
			schemeLoc = rand.nextInt(schemeList.length);
			authorityLoc = rand.nextInt(authorityList.length);
			pathLoc = rand.nextInt(pathList.length);
			queryLoc = rand.nextInt(queryList.length);
			
			if(!schemeList[schemeLoc].valid || !authorityList[authorityLoc].valid || !pathList[pathLoc].valid || !queryList[queryLoc].valid) {
				expectedValidity = false;
			}
			
			testString = schemeList[schemeLoc].item + authorityList[authorityLoc].item + pathList[pathLoc].item + queryList[queryLoc].item;
			actualValidity = testUrl.isValid(testString);
			assertEquals(testString, actualValidity, expectedValidity);
		}
	}
	
	
	/**
	 * Urls are constructed by: 
	 * <scheme>://<authority><path>?<query>
	 * This needs to be randomly generated
	 * This can be done by providing valid and invalid sections ie valid and invalid schemes
	 * And creating random combinations using the ResultPairs object arrays
	 */
	
	ResultPair[] schemeList = {
            new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false),
            new ResultPair("nonsense", false)};
	
	ResultPair[] authorityList = {new ResultPair("www.google.com", true),
            new ResultPair("www.google.com.", true),
            new ResultPair("go.com", true),
            new ResultPair("go.au", true),
            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("256.256.256.256", false),
            new ResultPair("255.com", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("1.2.3.4.", false),
            new ResultPair("1.2.3", false),
            new ResultPair(".1.2.3.4", false),
            new ResultPair("go.a", false),
            new ResultPair("go.a1a", false),
            new ResultPair("go.cc", true),
            new ResultPair("go.1aa", false),
            new ResultPair("aaa.", false),
            new ResultPair(".aaa", false),
            new ResultPair("aaa", false),
            new ResultPair("", false),
            new ResultPair("nonsense", false)};
	
	ResultPair[] pathList = {new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false),
            new ResultPair("nonsense", false)};
	
	ResultPair[] queryList = {new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true)};

}
