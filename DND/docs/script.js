document.addEventListener('DOMContentLoaded', function() {
    // Add smooth scrolling for anchor links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            const targetElement = document.querySelector(targetId);
            
            if (targetElement) {
                window.scrollTo({
                    top: targetElement.offsetTop - 80,
                    behavior: 'smooth'
                });
            }
        });
    });

    // Add active class to nav links based on current page
    const currentPath = window.location.pathname;
    const filename = currentPath.substring(currentPath.lastIndexOf('/') + 1);
    
    document.querySelectorAll('nav a').forEach(link => {
        const linkHref = link.getAttribute('href');
        if (linkHref === filename || (filename === '' && linkHref === 'index.html')) {
            link.classList.add('active');
        } else {
            link.classList.remove('active');
        }
    });

    // Add interaction to cards
    document.querySelectorAll('.card').forEach(card => {
        card.addEventListener('mouseenter', function() {
            this.style.transform = 'translateY(-10px)';
            this.style.boxShadow = '0 20px 25px -5px rgba(0, 0, 0, 0.1), 0 10px 10px -5px rgba(0, 0, 0, 0.04)';
        });
        
        card.addEventListener('mouseleave', function() {
            this.style.transform = 'translateY(0)';
            this.style.boxShadow = '0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06)';
        });
    });

    // Add accordion functionality for mobile documentation
    if (window.innerWidth < 768) {
        const docSidebar = document.querySelector('.doc-sidebar');
        if (docSidebar) {
            const tocHeading = docSidebar.querySelector('h3');
            const tocLinks = docSidebar.querySelector('ul');
            
            // Initially hide the TOC links on mobile
            tocLinks.style.display = 'none';
            
            // Add click event to toggle visibility
            tocHeading.addEventListener('click', function() {
                tocLinks.style.display = tocLinks.style.display === 'none' ? 'block' : 'none';
                tocHeading.classList.toggle('expanded');
            });
            
            // Add +/- indicator
            tocHeading.style.position = 'relative';
            tocHeading.style.cursor = 'pointer';
            const indicator = document.createElement('span');
            indicator.textContent = '+';
            indicator.style.position = 'absolute';
            indicator.style.right = '10px';
            tocHeading.appendChild(indicator);
            
            // Update indicator on click
            tocHeading.addEventListener('click', function() {
                indicator.textContent = indicator.textContent === '+' ? '-' : '+';
            });
        }
    }
});