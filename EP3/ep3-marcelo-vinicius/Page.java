/*
 *  Exercício Programa 3 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

public class Page {
    private boolean R;
    private int posVirtual;
    private int posPhysical;

    public Page (int p, int v) {
        this.posVirtual = v;
        this.posPhysical = p;
        this.R = false;
    }

	public int getR() {
        return R ? 1 : 0;
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
