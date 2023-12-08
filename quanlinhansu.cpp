#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;

class NhanVien {
public:
    static int nextMaNV;

    NhanVien(const std::string& hoTen, const std::string& diaChi, const std::string& soDT, int bacLuong)
        : maNV(nextMaNV++), hoTen(hoTen), diaChi(diaChi), soDT(soDT), bacLuong(bacLuong) {}

    void hienThiThongTin() const {
        std::cout << std::setw(8) << maNV << std::setw(20) << hoTen << std::setw(20) << diaChi
                  << std::setw(15) << soDT << std::setw(10) << bacLuong << std::endl;
    }

    int getMaNV() const { return maNV; }
    const std::string& getHoTen() const { return hoTen; }
    int getBacLuong() const { return bacLuong; }

private:
    int maNV;
    std::string hoTen;
    std::string diaChi;
    std::string soDT;
    int bacLuong;
};

int NhanVien::nextMaNV = 1000;

class PhongBan {
public:
    static int nextMaPB;

    PhongBan(const std::string& tenPhong, const std::string& moTa, double heSoCongViec)
        : maPB(nextMaPB++), tenPhong(tenPhong), moTa(moTa), heSoCongViec(heSoCongViec) {}

    void hienThiThongTin() const {
        std::cout << std::setw(8) << maPB << std::setw(20) << tenPhong << std::setw(20) << moTa
                  << std::setw(20) << heSoCongViec << std::endl;
    }

    int getMaPB() const { return maPB; }
    const std::string& getTenPhong() const { return tenPhong; }
    double getHeSoCongViec() const { return heSoCongViec; }

private:
    int maPB;
    std::string tenPhong;
    std::string moTa;
    double heSoCongViec;
};

int PhongBan::nextMaPB = 100;

class BangChamCong {
public:
    BangChamCong(const NhanVien& nv, const PhongBan& pb, int soNgay)
        : nhanVien(nv), phongBan(pb), soNgayLamViec(soNgay) {}

    void hienThiThongTin() const {
        nhanVien.hienThiThongTin();
        phongBan.hienThiThongTin();
        std::cout << "So Ngay Lam Viec: " << soNgayLamViec << std::endl;
    }

    const NhanVien& getNhanVien() const { return nhanVien; }
    const PhongBan& getPhongBan() const { return phongBan; }
    int getSoNgayLamViec() const { return soNgayLamViec; }

    // Comparison operators for sorting
    static int compareNhanVienByName(const void* a, const void* b) {
        return ((BangChamCong*)a)->getNhanVien().getHoTen() < ((BangChamCong*)b)->getNhanVien().getHoTen() ? -1 : 1;
    }

    static int compareBangChamCongByPhongBan(const void* a, const void* b) {
        return ((BangChamCong*)a)->getPhongBan().getTenPhong() < ((BangChamCong*)b)->getPhongBan().getTenPhong() ? -1 : 1;
    }

private:
    const NhanVien& nhanVien;
    const PhongBan& phongBan;
    int soNgayLamViec;
};
// Hàm tính thu nhập
double tinhThuNhap(const NhanVien& nhanVien, const PhongBan& phongBan, int soNgayLamViec) {
    if (soNgayLamViec < 0) {
        std::cerr << "Số ngày làm việc không hợp lệ.\n";
        return 0.0;
    }

    double luongCoBan = 850000.0;
    double heSoBacLuong = 2 + nhanVien.getBacLuong() / 3.0;
    double heSoCongViec = phongBan.getHeSoCongViec();
    double soNgayLamViecTrongThang = 22.0;

    // Đảm bảo chia số ngày làm việc làm số thực
    double thuNhap = luongCoBan * heSoBacLuong * heSoCongViec * (static_cast<double>(soNgayLamViec) / soNgayLamViecTrongThang);

    // Đảm bảo thu nhập không âm
    thuNhap = (thuNhap < 0.0) ? 0.0 : thuNhap;

    return thuNhap;
}
// Hàm kiểm tra xem một nhân viên đã làm việc ở một phòng ban hay chưa
bool kiemTraNhanVienLamViecOPhongBan(const std::vector<BangChamCong>& danhSachChamCong,
                                     const NhanVien& nhanVien, const PhongBan& phongBan) {
    for (const auto& cc : danhSachChamCong) {
        if (&cc.getNhanVien() == &nhanVien && &cc.getPhongBan() == &phongBan) {
            return true; // Nhân viên đã làm việc ở phòng ban này
        }
    }
    return false; // Nhân viên chưa làm việc ở phòng ban này
}

// Hàm nhập thông tin chấm công
void nhapDanhSachChamCong(std::vector<BangChamCong>& danhSachChamCong,
                          const std::vector<NhanVien>& danhSachNhanVien,
                          const std::vector<PhongBan>& danhSachPhongBan) {
    for (const auto& nv : danhSachNhanVien) {
        for (const auto& pb : danhSachPhongBan) {
            // Kiểm tra xem nhân viên đã làm việc ở phòng ban này chưa
            if (!kiemTraNhanVienLamViecOPhongBan(danhSachChamCong, nv, pb)) {
                int soNgayLamViec;
                std::cout << "Nhap so ngay lam viec cho nhan vien " << nv.getHoTen()
                          << " o phong " << pb.getTenPhong() << ": ";
                std::cin >> soNgayLamViec;

                danhSachChamCong.push_back(BangChamCong(nv, pb, soNgayLamViec));
            } else {
                std::cout << "Nhan vien " << nv.getHoTen() << " da lam viec o phong ban nay. Khong the chon phong ban nay.\n";
            }
        }
    }
}

// Hàm in ra bảng chấm công chỉ có mã NV, tên NV, mã PB, tên phòng và số ngày làm việc
void inBangChamCong(const std::vector<BangChamCong>& danhSachChamCong) {
	cout<<"\n";
	cout<<"\n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << "                               DANH SACH CHAM CONG                             \n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << std::setw(8) << "MA NV" << std::setw(20) << "TEN NV" << std::setw(10) << "MA PB"
         << std::setw(20) << "TEN PHONG" << std::setw(20) << "SO NGAY LAM VIEC" << std::endl;

    for (const auto& cc : danhSachChamCong) {
        cout << std::setw(8) << cc.getNhanVien().getMaNV()
             << std::setw(20) << cc.getNhanVien().getHoTen()
             << std::setw(8) << cc.getPhongBan().getMaPB()
             << std::setw(20) << cc.getPhongBan().getTenPhong()
             << std::setw(20) << cc.getSoNgayLamViec() << std::endl;
    }
}

// Hàm nhập danh sách nhân viên mới
void nhapDanhSachNhanVien(std::vector<NhanVien>& danhSachNhanVien) {
    int soLuong;
    std::cout << "Nhap so luong nhan vien moi: ";
    std::cin >> soLuong;

    for (int i = 0; i < soLuong; ++i) {
        std::string hoTen, diaChi, soDT;
        int bacLuong;

        std::cout << "Nhap thong tin cho nhan vien thu " << i + 1 << ":\n";
        std::cout << "Ho Ten: ";
        std::cin.ignore(); // Đảm bảo getline không bị ảnh hưởng bởi enter trước đó
        std::getline(std::cin, hoTen);

        std::cout << "Dia Chi: ";
        std::getline(std::cin, diaChi);

        std::cout << "So DT: ";
        std::getline(std::cin, soDT);

        std::cout << "Bac Luong: ";
        std::cin >> bacLuong;

        danhSachNhanVien.push_back(NhanVien(hoTen, diaChi, soDT, bacLuong));
    }
}

// Hàm nhập danh sách phòng ban
void nhapDanhSachPhongBan(std::vector<PhongBan>& danhSachPhongBan) {
    int soLuong;
    std::cout << "Nhap so luong phong ban: ";
    std::cin >> soLuong;

    for (int i = 0; i < soLuong; ++i) {
        std::string tenPhong, moTa;
        double heSoCongViec;

        std::cout << "Nhap thong tin cho phong ban thu " << i + 1 << ":\n";
        std::cout << "Ten Phong: ";
        std::cin.ignore(); // Đảm bảo getline không bị ảnh hưởng bởi enter trước đó
        std::getline(std::cin, tenPhong);

        std::cout << "Mo Ta: ";
        std::getline(std::cin, moTa);

        std::cout << "He So Cong Viec: ";
        std::cin >> heSoCongViec;

        danhSachPhongBan.push_back(PhongBan(tenPhong, moTa, heSoCongViec));
    }
}

int main() {
    std::vector<NhanVien> danhSachNhanVien;
    std::vector<PhongBan> danhSachPhongBan;
    std::vector<BangChamCong> danhSachChamCong;

    // Nhập danh sách nhân viên mới
    nhapDanhSachNhanVien(danhSachNhanVien);

    // Nhập danh sách phòng ban mới
    nhapDanhSachPhongBan(danhSachPhongBan);

    // Nhập thông tin chấm công
    nhapDanhSachChamCong(danhSachChamCong, danhSachNhanVien, danhSachPhongBan);

    // Hiển thị thông tin
    cout << "-------------------------------------------------------------------------------\n";
    cout << "                               DANH SACH NHAN VIEN                             \n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << std::setw(8) << "MA NV" << std::setw(20) << "HOTEN" << std::setw(20) << "DIA CHI"
         << std::setw(15) << "SO DT" << std::setw(15) << "BAC LUONG" << std::endl;
    for (const auto& nv : danhSachNhanVien) {
        nv.hienThiThongTin();
    }
    cout << "\n";
    cout<<"\n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << "                               DANH SACH PHONG BAN                             \n";
    cout << "-------------------------------------------------------------------------------\n";
    std::cout << std::setw(8) << "MA PB" << std::setw(20) << "TEN PHONG" << std::setw(20) << "MO TA"
              << std::setw(20) << "HE SO CONG VIEC" << std::endl;
    for (const auto& pb : danhSachPhongBan) {
        pb.hienThiThongTin();
    }

    // In bảng chấm công
    inBangChamCong(danhSachChamCong);

    // Sắp xếp theo tên nhân viên
    qsort(&danhSachChamCong[0], danhSachChamCong.size(), sizeof(BangChamCong),
          BangChamCong::compareNhanVienByName);

    // Sắp xếp theo phòng ban
    qsort(&danhSachChamCong[0], danhSachChamCong.size(), sizeof(BangChamCong),
          BangChamCong::compareBangChamCongByPhongBan);

    // Thống kê thu nhập
std::cout << "\nBang thong ke thu nhap:\n";
for (const auto& cc : danhSachChamCong) {
    double thuNhap = tinhThuNhap(cc.getNhanVien(), cc.getPhongBan(), cc.getSoNgayLamViec());
    std::cout << "Ma NV: " << cc.getNhanVien().getMaNV() << ", Ho Ten: " << cc.getNhanVien().getHoTen()
              << ", Thu Nhap: " << thuNhap << std::endl;
}
	return 0;
}