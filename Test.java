
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;


class A {
	public int a = 1;
}

class B extends A {
	
}

class Point1 {
	public int x, y;
	public Point1(int a, int b) {
		x = a;
		y = b;
	}
}

public class Test {

	/**
	 * @param args
	 */

	
	public int direction(Point1 a, Point1 b , Point1 k) {
		int res = (a.x - k.x) * (b.y - k.y) -( a.y - k.y ) * (b.x - k.x);
		if (res < 0)
			return -1;
		if (res >0)
			return 1;
		return 0;
	}
	
	public boolean onSegment(Point1 a, Point1 b, Point1 k) {
		int minx, miny, maxx, maxy;
		
		if (a.x > b.x) {
			minx = b.x;
			maxx = a.x;
		}
		else {
			minx = a.x;
			maxx = b.x;
		}
		
		if (a.y > b.y) {
			miny = b.y;
			maxy = a.y;
		}
		else {
			miny = a.y;
			maxy = b.y;
		}
		
		if (k.x >= minx && k.x <= maxx && k.y >= miny && k.y <= maxy)
			return true;
		return false;
	}
	
	public boolean segmentIntersect(Point1 p1, Point1 p2, Point1 p3, Point1 p4) {
		int d1 = direction(p1, p2, p3);
		int d2 = direction(p1, p2, p4);
		int d3 = direction(p3, p4, p1);
		int d4 = direction(p3, p4, p2);
		
		if (d1*d2 < 0 && d3*d4 < 0)
			return true;
		
		if (d1 == 0 && onSegment(p1, p2, p3))
			return true;
		if(d2 == 0 && onSegment(p1, p2, p4))
			return true;
		if(d3 ==0 && onSegment(p3, p4, p1))
			return true;
		if(d4 ==0 && onSegment(p3, p4, p2))
			return true;
		return false;
	}
	
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
//		System.out.println(t.segmentIntersect(new Point(0,0), new Point(1,1), new Point(0,1), new Point(1,0)));
//		
//		System.out.println(t.segmentIntersect(new Point(2,2), new Point(1,1), new Point(3,0), new Point(3,8)));
//		
//		System.out.println(t.segmentIntersect(new Point(0,0), new Point(1,1), new Point(0,0), new Point(5,7)));
		
		
		
		
		
	}

}

class C extends A {
	
}

