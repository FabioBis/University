package javax.constraints.impl.constraint;

import javax.constraints.impl.Constraint;
import javax.constraints.impl.Problem;

/**
 * Implements a constraint representing the conjunction of two
 * given other constraints.
 * 
 * @author Fabio Biselli
 *
 */
public class And extends Constraint {

	/**
	 * Build a new Constraint <code>c</code> from two given Constraint(s) 
	 * <code>c1</code> and <code>c2</code> such as:
	 * <p align=center><code>c = c1 and c2</code>.</p>
	 * 
	 * @param c1 first Constraint
	 * @param c2 second Constraint.
	 */
	public And(Constraint c1, Constraint c2) {
		super(c1.getProblem());
//		Constraint result = (Constraint) 
//			((c1.negation()).or(c2.negation())).negation();
		Constraint result = c1.and(c2);
		setImpl(result.getImpl());
	}
	
	public void post() {
		((Problem) getProblem()).post(this);
	}

}
