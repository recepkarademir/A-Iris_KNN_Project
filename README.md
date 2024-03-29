![3D_dataset](3d_dataset.png) [![License](https://img.shields.io/badge/license-MIT-green.svg?style=flat)](https://github.com/recepkarademir/A-Iris_KNN_Project/blob/master/LICENSE)

# IRIS classification using KNN
# Iris veri setini KNN ile sınıflandırma
------------------------------
2018 Aralık v3.1.3

Recep KARADEMİR
____________________________________________________________________________________________________________________________________

Özet:
------------------------------
Projenin detaylı raporu için Iris_KNN_Projesi.pdf dosyasını inceleyin.

IRIS : Süsengiller (Iris), Asparagales takımına ait bir çiçekli bitki familyasıdır.
Iris familyasındaki üç türün temel özelliklerinden oluşan veriler yardımıyla,
en iyi tür tahmini yapabilen K (KNN) tespiti yapabileceğimiz program yazılmıştır.
Bu proje C++ programlama dilinde, K-En Yakın Komşu algoritması kullanılarak hazırlanmıştır.
Program iris.txt içindeki iris çiçeği verilerini üç sete ayırarak işlem yapmaktadır.
İlk iki seti programı eğitme amaçlı kullanan, üçüncü seti ise koruyarak test amaçlı tutan bir program yazılmıştır.
Okuduğu veri setini istersek karıştırarak işleyebiliriz(her veri setinde her iris sınıfından örnekler bulunması için).
Program v2.0 güncellemesinden sonra test setindeki bir veriyi tahmin etme işlemini de yapabilmektedir.

------------------------------


GİRİŞ
------------------------------
Program iris.txt içindeki iris çiçeği verilerini üç sete ayırarak işlem yapmaktadır.<br/>
İlk seti eğitim seti olarak saklar. İlk set toplam veri setinin %50 sini oluşturacak şekilde ayrılır.<br/>
Rastgele karıştırılan verinin ilk % 50 lik kısmı program tarafından eğitim seti olur.<br/>
ikinci seti toplam veri setinin %25'ini (%50 lik kısmın üstündeki %25 lik kısım) ve
üçüncü seti toplam veri setinin %25(%75 den sonraki kalan %25 lik kısım) 'ini oluşturacak şekilde ayırır.<br/>
İlk %50 lik set eğitim setimizdir. İkinci %25 lik set doğrulama setimizdir. Üçüncü %25 lik set test setimizdir.<br/>
Doğrulama setinin ilk indisi, 150 adet veri içeren veri setinde 75.indis olacaktır.<br/>
Test setinin ilk indisi , 150 adet veri içeren veri setinde 113.indis olacaktır.<br/>
Eğitim seti [0..74] verileridir. Doğrulama seti [75..112] verileri olacaktır. Test seti [113..149] indislerideki veriler olur.<br/>
Veriler txt içerisinde aralarında boş satır olmayacak şekilde bulunmalıdır.<br/>
Her satırdaki iris özellikleri aralarına virgül koyularak ayrılmış olmalıdır.<br/>

Okunan txt verilerinden Iris adları bellekte işlem kolaylığı olması amaçlı 0 ,1 ,2 olacak şekilde kodlanarak tutuluyor.<br/>
0 kodu iris-setosa , 1 kodu iris-versicolor , 2 kodu iris-virginica olarak bellekte tutulacaklar.
Program içerisinde iris adlarının kodları yerine adların kendilerini metin olarak göreceğiz.

------------------------------
![knn=3](Knn_example.jpg)


K değerinin incelenmesi
------------------------------
Hata oranının artması, veri setindeki özellik değerlerinin birbirine yakın olması veya k değerinin bir iris türü adının (her tür için 50 tane var) adet sayısına(50ye yakın) yakın veya üzeri bir değer olmasına bağlıdır.
K için 37-38-39-40-41 gibi üzeri her değer programın tahmininde hata sayısının çoğalmasına neden olur.
Bunun sebebi tür adetinden fazla k değeri girildiğinde komşuluk farkının başka türleri de kapsamasıdır.

------------------------------

Yaptığım testler sonucu en iyi k değerlerinin 1,2,3,4,5 gibi değerler olduğunu buldum.
<br/>En kötü değerler ise 35 ve üzeri k değerleri için oldu.<br/>
Test setindeki başarı oranı, eğitim+doğrulama seti tahmin başarı oranından daha fazla.<br/> Bunun sebebi test setinde 
kontrol edilen örnek sayısının fazla olmasıydı. 
<br/>Kod parçası , algoritma işleyişi ve bu doküman hakkındaki sorularınızı bana iletebilirsiniz.<br/>
___________________________________________________________________________________________________________________________________

İletişim
------------------------------

recepkarademir0018@gmail.com

https://recepkarademir.blogspot.com.tr

https://recepkarademir.wordpress.com

## BU PROJENİN KULLANILABİLİRLİK SEVİYESİ: 7/10
