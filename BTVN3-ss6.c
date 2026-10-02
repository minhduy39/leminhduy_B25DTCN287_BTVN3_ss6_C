#include <stdio.h>
#include <string.h>

#define MAX 100
#define HAN_MUON 14
#define PHI_PHAT_NGAY 5000

// Ham xoa sach ky tu con sot trong bo dem ban phim (Buffer Flush)
void xoaBoDem(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    // Khai bao cac mang song song quan ly du lieu
    char maPhieu[MAX][20];
    char maSach[MAX][20];
    int soNgayMuon[MAX];

    int soLuong = 0; // Bien dem so luong phieu muon hien tai
    int luaChon;

    do {
        printf("\n================ HE THONG QUAN LY MUON TRA SACH (LOGISTICS) ================\n");
        printf("1. Them moi phieu muon sach (Create)\n");
        printf("2. Hien thi danh sach phieu muon & Tien phat qua han (Read)\n");
        printf("3. Cap nhat so ngay muon sach (Update)\n");
        printf("4. Xac nhan tra sach / Xoa phieu muon (Delete)\n");
        printf("5. Thoat chuong trinh\n");
        printf("===========================================================================\n");
        printf("Lua chon cua ban (1-5): ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long nhap so nguyen tu 1 den 5!\n");
            xoaBoDem();
            continue;
        }

        xoaBoDem(); // Xoa ky tu \n con sot sau khi nhap luaChon

        switch (luaChon) {
            case 1: {
                // YEU CAU 1: THEM MOI PHIEU MUON (CREATE)
                printf("\n--- THEM MOI PHIEU MUON ---\n");

                // Kiem tra bo nho mang
                if (soLuong >= MAX) {
                    printf("Bo nho danh sach da day, khong the them moi!\n");
                    break;
                }

                char maMoi[20];
                printf("Nhap ma phieu: ");
                scanf("%19s", maMoi);
                xoaBoDem();

                // Kiem tra trung lap ma phieu bang strcmp()
                int maTrungLap = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maMoi) == 0) {
                        maTrungLap = 1;
                        break;
                    }
                }

                if (maTrungLap) {
                    printf("Ma phieu da ton tai trong he thong!\n");
                    break;
                }

                // Luu ma phieu hop le
                strcpy(maPhieu[soLuong], maMoi);

                // Nhap ma sach
                printf("Nhap ma sach: ");
                scanf("%19s", maSach[soLuong]);
                xoaBoDem();

                // Nhap so ngay muon (soNgayMuon > 0)
                int ngay;
                do {
                    printf("Nhap so ngay muon: ");
                    if (scanf("%d", &ngay) != 1 || ngay <= 0) {
                        printf("So ngay muon phai la so nguyen duong (> 0). Vui long nhap lai!\n");
                        xoaBoDem();
                        ngay = -1;
                    } else {
                        xoaBoDem();
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;
                soLuong++;

                printf("Them moi phieu muon thanh cong!\n");
                break;
            }

            case 2: {
                // YEU CAU 2: HIEN THI DANH SACH & TINH TIEN PHAT (READ)
                if (soLuong == 0) {
                    printf("\nDanh sach phieu muon hien dang rong!\n");
                    break;
                }

                printf("\n================================ DANH SACH PHIEU MUON ================================\n");
                printf("%-5s %-12s %-12s %-10s %-15s %-18s\n", 
                       "STT", "MA PHIEU", "MA SACH", "SO NGAY", "TRANG THAI", "TIEN PHAT (VND)");
                printf("-------------------------------------------------------------------------------------\n");

                long long tongTienPhat = 0;

                for (int i = 0; i < soLuong; i++) {
                    int ngay = soNgayMuon[i];
                    long long tienPhat = 0;
                    char trangThai[15];

                    // Tinh tien phat va xac dinh trang thai
                    if (ngay > HAN_MUON) {
                        int ngayQuaHan = ngay - HAN_MUON;
                        tienPhat = (long long)ngayQuaHan * PHI_PHAT_NGAY;
                        strcpy(trangThai, "QUA HAN");
                    } else {
                        tienPhat = 0;
                        strcpy(trangThai, "DUNG HAN");
                    }

                    tongTienPhat += tienPhat;

                    printf("%-5d %-12s %-12s %-10d %-15s %-18lld\n", 
                           i + 1, maPhieu[i], maSach[i], ngay, trangThai, tienPhat);
                }

                printf("================================================================---------------------\n");
                printf("Tong tien phat toan he thong: %lld VND\n", tongTienPhat);
                break;
            }

            case 3: {
                // YEU CAU 3: CAP NHAT SO NGAY MUON (UPDATE)
                if (soLuong == 0) {
                    printf("\nDanh sach phieu muon hien dang rong!\n");
                    break;
                }

                char maTim[20];
                printf("\nNhap ma phieu can cap nhat: ");
                scanf("%19s", maTim);
                xoaBoDem();

                // Tim kiem tuyen tinh vi tri pos
                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTim) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu trong he thong!\n");
                } else {
                    printf("So ngay muon hien tai cua phieu %s la: %d\n", maPhieu[pos], soNgayMuon[pos]);

                    int ngayMoi;
                    do {
                        printf("Nhap so ngay muon moi: ");
                        if (scanf("%d", &ngayMoi) != 1 || ngayMoi <= 0) {
                            printf("So ngay muon phai la so nguyen duong (> 0). Vui long nhap lai!\n");
                            xoaBoDem();
                            ngayMoi = -1;
                        } else {
                            xoaBoDem();
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[pos] = ngayMoi;
                    printf("Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: {
                // YEU CAU 4: XAC NHAN TRA SACH / XOA PHIEU MUON (DELETE)
                if (soLuong == 0) {
                    printf("\nDanh sach phieu muon hien dang rong!\n");
                    break;
                }

                char maXoa[20];
                printf("\nNhap ma phieu xac nhan tra/xoa: ");
                scanf("%19s", maXoa);
                xoaBoDem();

                // Tim kiem tuyen tinh vi tri pos
                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maXoa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu can xoa!\n");
                } else {
                    // Doi cac phan tu phia sau len 1 vi tri
                    for (int i = pos; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(maSach[i], maSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                    }

                    soLuong--; // Giam so luong phieu
                    printf("Xac nhan tra sach va xoa phieu muon thanh cong!\n");
                }
                break;
            }

            case 5:
                // YEU CAU 5: THOAT CHUONG TRINH
                printf("\nCam on ban da su dung HE THONG QUAN LY MUON TRA SACH (LOGISTICS)!\n");
                printf("Tam biet va hen gap lai.\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
                break;
        }

    } while (luaChon != 5);

    return 0;
}
