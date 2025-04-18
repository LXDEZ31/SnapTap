# SnapTap Movement Optimizer

SnapTap, oyuncuların klavye girdilerine göre hareket verimliliğini artıran deneysel bir C++ projesidir. Özellikle FPS oyunlarında (Valorant gibi) daha hızlı ve kontrollü hareket tepkisi elde etmeyi hedefler.

## 🧠 Özellikler

- Snap-tap tarzı hareket sistemi.
- Counter-strafe desteği (hareketi durdurma süresini kısaltır).
- Double-tap özelliği (isteğe bağlı).
- Terminal tabanlı kontrol: Aç/kapat ve durum kontrolü.
- Düşük farklarla yapılan input taklidi sayesinde doğal hissettirir.

## 🚀 Nasıl Çalışır?

Uygulama başlatıldığında terminalde aktif olup olmadığı gösterilir.  
SnapTap sistemi otomatik olarak aktif hale gelir.

### Komutlar:

- `kapat`: Uygulamayı durdurur ve terminali temizler.
- `çık`: Programı tamamen kapatır.
- Varsayılan olarak **Insert** tuşuyla aktif/pasif olur.

## 🖥️ Sistem Gereksinimleri

- Windows 10 veya üzeri
- C++17 destekli bir sistem
- Admin izni gerekebilir (klavye hook işlemleri için)

## ⚠️ Uyarı

Bu proje yalnızca **eğitimsel ve deneysel** amaçlarla geliştirilmiştir.  
Online oyunlarda kullanımı oyun kurallarına aykırı olabilir.  
Herhangi bir yaptırımdan geliştirici sorumlu değildir.

## 📁 Derleme

Visual Studio veya g++ kullanarak derleyebilirsin:

```bash
g++ main.cpp -o snaptap.exe
