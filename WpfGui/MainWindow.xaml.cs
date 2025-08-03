#define DEBUG  
using CppCliWrapper;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Media;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Demon_battle
{
    public partial class MainWindow : Window
    {
        Wrapper game;
        static private SoundPlayer player;
        private List<int> selectedCardIndices = new List<int>();
        private int requiredCardSelections = 3;

        public MainWindow()
        {
            InitializeComponent();
            game = new Wrapper(); 
            player = new SoundPlayer("../../../../Sound/background.wav");
            player.PlayLooping();

            // Register C# function to be called from C++
            Wrapper.RegisterImageCallback(ShowImages);
            Wrapper.RegisterAvailableCardsCallback(ShowAvailableCards);
            
            // Show menu panel initially
            MenuPanel.Visibility = Visibility.Visible;
            GamePanel.Visibility = Visibility.Collapsed;
            CharacterSelectionPanel.Visibility = Visibility.Collapsed;
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {

            player.Stop();
            // 게임 시작을 백그라운드 쓰레드로 실행
            Task.Run(() =>
            {
                game.StartGame(); // native C++ 게임 루프
            });
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }

        private void MenuStartGame_Click(object sender, RoutedEventArgs e)
        {
            MenuPanel.Visibility = Visibility.Collapsed;
            CharacterSelectionPanel.Visibility = Visibility.Visible;
        }

        private void MenuExitGame_Click(object sender, RoutedEventArgs e)
        {
            // Hide game panels
            GamePanel.Visibility = Visibility.Collapsed;
            AvailableCardsPanel.Visibility = Visibility.Collapsed;
            CharacterSelectionPanel.Visibility = Visibility.Collapsed;

            // Show main menu
            MenuPanel.Visibility = Visibility.Visible;
        }

        private void SelectPikachu_Click(object sender, RoutedEventArgs e)
        {
            StartGameWithCharacter(0); // 0 = Pikachu
        }

        private void SelectKkobugi_Click(object sender, RoutedEventArgs e)
        {
            StartGameWithCharacter(1); // 1 = Kkobugi
        }

        private void SelectPairi_Click(object sender, RoutedEventArgs e)
        {
            StartGameWithCharacter(2); // 2 = Pairi
        }

        private void StartGameWithCharacter(int characterId)
        {
            CharacterSelectionPanel.Visibility = Visibility.Collapsed;
            
            // Start game in background thread with the selected character
            Task.Run(() =>
            {
                game.SelectCharacter(characterId);
                game.StartGame(); 
            });
        }

        public static void ShowImages(List<List<string>> paths, int playerCurrentHp, int playerMaxHp, int computerCurrentHp, int computerMaxHp, string sound_path)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                string a = "../../../../Sound/background.wav";
                bool ais = a == sound_path;
                player = new SoundPlayer(sound_path);
                player.Play();
                var window = (MainWindow)Application.Current.MainWindow;

                window.ImageGrid.Children.Clear();
                window.ImageGrid.RowDefinitions.Clear();
                window.ImageGrid.ColumnDefinitions.Clear();

                window.GamePanel.Visibility = Visibility.Visible;

                //update HP Bars
                window.playerHpBar.Maximum = playerMaxHp;
                window.computerHpBar.Maximum = computerMaxHp;
                window.playerHpBar.Value = playerCurrentHp;
                window.computerHpBar.Value = computerCurrentHp;
                window.playerHpText.Text = $"{playerCurrentHp} / {playerMaxHp}";
                window.computerHpText.Text = $"{computerCurrentHp} / {computerMaxHp}";

                int rowCount = paths.Count;
                int colCount = paths[0].Count;

                for (int r = 0; r < rowCount; r++)
                    window.ImageGrid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(200) });

                for (int c = 0; c < colCount; c++)
                    window.ImageGrid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(200) });

                for (int r = 0; r < rowCount; r++)
                {
                    for (int c = 0; c < colCount; c++)
                    {
                        string path = paths[r][c];

                        if (string.IsNullOrWhiteSpace(path))
                        {
                            var rect = new Border
                            {
                                Background = Brushes.White,
                                BorderBrush = Brushes.Gray,
                                BorderThickness = new Thickness(1)
                            };
                            Grid.SetRow(rect, r);
                            Grid.SetColumn(rect, c);
                            window.ImageGrid.Children.Add(rect);
                        }
                        else
                        {

                            string fullPath = System.IO.Path.GetFullPath(path);
                            if (!File.Exists(path))
                            {
                                Debug.WriteLine($"[ERROR] 파일이 존재하지 않습니다: {path}");
                                continue;
                            }

                            // 이미지 불러오기 (캐시 무시)
                            var bitmap = new BitmapImage();
                            bitmap.BeginInit();
                            bitmap.CacheOption = BitmapCacheOption.OnLoad;  // 캐시 무시
                            bitmap.UriSource = new Uri(fullPath, UriKind.Absolute); 
                            bitmap.DecodePixelWidth = 100; // 또는 실제 이미지 크기나 ImageControl 크기에 맞춰 조정
                            bitmap.EndInit();

                            // 새 Image 객체 생성
                            var image = new Image
                            {
                                Source = bitmap,
                                Width = 150,
                                Height = 150,
                                Stretch = Stretch.UniformToFill,
                                HorizontalAlignment = HorizontalAlignment.Center,
                                VerticalAlignment = VerticalAlignment.Center
                            };

                            // 강제 렌더링 트릭
                            RenderOptions.SetBitmapScalingMode(image, BitmapScalingMode.HighQuality);
                            //RenderOptions.SetCachingHint(image, CachingHint.Uncache);

#if DEBUG
                            // Grid에 삽입
                            Grid.SetRow(image, r);
                            Grid.SetColumn(image, c);
                            window.ImageGrid.Children.Add(image);

                            var label = new TextBlock
                            {
                                Text = $"{r},{c}",
                                Foreground = Brushes.Red,
                                FontSize = 10,
                                VerticalAlignment = VerticalAlignment.Top,
                                HorizontalAlignment = HorizontalAlignment.Left
                            };
                            Grid.SetRow(label, r);
                            Grid.SetColumn(label, c);
                            window.ImageGrid.Children.Add(label);
#endif

                        }
                    }
                }
            });
        }
        
        public static void ShowAvailableCards(List<string> availableCardNames, List<string> cardImagePaths)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                var window = (MainWindow)Application.Current.MainWindow;

                window.GamePanel.Visibility = Visibility.Visible;
                window.AvailableCardsPanel.Visibility = Visibility.Visible;

                // Clear previous selections
                window.selectedCardIndices.Clear();
                
                // Display available cards with selection buttons and images
                window.availableCardsList.Items.Clear();
                for (int i = 0; i < availableCardNames.Count; i++)
                {
                    var cardPanel = new StackPanel { Orientation = Orientation.Horizontal };
                    
                    // Add card image
                    var cardImage = new Image { Width = 60, Height = 60, Margin = new Thickness(5) };
                    try {
                        string fullPath = System.IO.Path.GetFullPath(cardImagePaths[i]);
                        if (File.Exists(fullPath))
                        {
                            var bitmap = new BitmapImage();
                            bitmap.BeginInit();
                            bitmap.CacheOption = BitmapCacheOption.OnLoad;
                            bitmap.UriSource = new Uri(fullPath, UriKind.Absolute);
                            bitmap.DecodePixelWidth = 60;
                            bitmap.EndInit();
                            cardImage.Source = bitmap;
                        }
                        else
                        {
                            Debug.WriteLine($"[ERROR] Card image not found: {cardImagePaths[i]}");
                        }
                    }
                    catch (Exception ex) {
                        Debug.WriteLine($"[ERROR] Loading card image: {ex.Message}");
                    }
                    
                    var cardName = new TextBlock { 
                        Text = availableCardNames[i], 
                        Margin = new Thickness(5), 
                        Width = 150,
                        VerticalAlignment = VerticalAlignment.Center
                    };
                    
                    var selectButton = new Button { Content = "Select", Tag = i };
                    selectButton.Click += window.CardSelect_Click;
                    
                    cardPanel.Children.Add(cardImage);
                    cardPanel.Children.Add(cardName);
                    cardPanel.Children.Add(selectButton);
                    
                    window.availableCardsList.Items.Add(cardPanel);
                }
                
                // Show confirmation button
                window.confirmCardSelection.Visibility = Visibility.Visible;
                window.confirmCardSelection.IsEnabled = false;
            });
        }

        private void CardSelect_Click(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;
            int cardIndex = (int)button.Tag;
            
            // Add to selection if not already selected and we haven't reached the limit
            if (!selectedCardIndices.Contains(cardIndex) && selectedCardIndices.Count < requiredCardSelections)
            {
                selectedCardIndices.Add(cardIndex);
                button.IsEnabled = false;
                button.Content = "Selected";
            }
            
            // Enable confirm button if we have enough selections
            confirmCardSelection.IsEnabled = selectedCardIndices.Count == requiredCardSelections;
        }

        private void ConfirmCardSelection_Click(object sender, RoutedEventArgs e)
        {
            // Submit selected cards back to C++
            Wrapper.SubmitCardSelections(new List<int>(selectedCardIndices));

            // Hide selection panel
            AvailableCardsPanel.Visibility = Visibility.Collapsed;
            confirmCardSelection.Visibility = Visibility.Collapsed;
            
            // Reset for next selection
            selectedCardIndices.Clear();
        }
    }
}