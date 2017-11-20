public class Page {
    private boolean R;
    private int posVirtual;
    private int posPhysical;

    public Page (int p, int v) {
        this.posVirtual = v;
        this.posPhysical = p;
        this.R = false;
    }

	public boolean getR() {
		return R;
	}

	public void setR(boolean R) {
		this.R = R;
	}

	public int getPosVirtual() {
		return posVirtual;
	}

	public void setPosVirtual(int posVirtual) {
		this.posVirtual = posVirtual;
	}

	public int getPosPhysical() {
		return posPhysical;
	}

	public void setPosPhysical(int posPhysical) {
		this.posPhysical = posPhysical;
	}
}
